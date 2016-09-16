#include <Adafruit_Thermal.h>
#include <SPI.h>
#include <MFRC522.h>

#include "SoftwareSerial.h"   // for printer

#include "defines.h"
#include "prototypes.h"

//#include "cards.h"

#include "cardList.h"
#include "jobStrings.h"

/*RFID Init*/
#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
MFRC522::MIFARE_Key key;

/* Printer Init*/
#define TX_PIN 6 // Arduino pin 6 for  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino pin 5 for   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor
/*misc global vars*/

byte lastCard[] = {0,0,0,0,0,0};
unsigned long newCardID; 
long lastUidRead; //For storing time of last read UID
unsigned int status = STATUS_POWER_ON;


void setup() {
  
	Serial.begin(9600);		// Initialize serial communications with the PC
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details

  // NOTE: SOME PRINTERS NEED 9600 BAUD instead of 19200, check test page.
  mySerial.begin(19200);  // Initialize SoftwareSerial
  //Serial1.begin(19200); // Use this instead if using hardware serial
  printer.begin();        // Init printer (same regardless of serial type)
  
  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  lastUidRead = 0;
  
  Serial.println(F("Generic welcome message"));
  printer.println(F("Generic welcome message\n"));

  updateStatus(STATUS_READY);
 }

void loop() {
  
   
	if ((millis()-lastUidRead) > 2000) {
   updateStatus(STATUS_READY); 
	// Look for new cards
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}
	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
    delay(50);
	}
    
        //printCardID(); 
        //updateLastCard(lastCard, mfrc522.uid.size);
        
        newCardID = UIDBytesIntoLong(mfrc522.uid.uidByte, mfrc522.uid.size);  
        
        if (!isCardInList(&newCardID)){
          //If it isnt in list, failstate
          Serial.println("ERROR - CARD IS NOT VALID");
        } else {
          updateStatus(STATUS_PRINTING);
          printCurrentJobTicket(&newCardID);
          incrementJobIndex(&newCardID);
          updateStatus(STATUS_TAKE_TICKET);
          //delay(200);
        }
        lastUidRead = millis();
    }
}

int cardCmp(byte *cardID1, byte *cardID2, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
      if (cardID1[i] != cardID2[i]){
        return 0; //is not equal
      }
    }
    return 1; //is equal
}

int isCardInList(unsigned long *newCardID){
  //compared unsigned long to each element in list
  for (int i = 0; i < MAX_CARDS; i++) {
     if (cards[i].cardID == *newCardID){
      Serial.println("is in list");
      return 1; //is in list
     }
  }
  Serial.println("not in list");
  return 0; //is not in list
}


//DEBUGGING
void dumpCardList(){
  for (int i = 0; i < MAX_CARDS; i++) {
      Serial.print("Card #");
      Serial.print(i);
      Serial.print(" : ");
      Serial.print(cards[i].cardID);
      Serial.print(" : ");
      Serial.print(cards[i].currentJobIndex);
      Serial.print(" : ");
      for (int ji = 0; ji < MAX_JOBS_PER_CARD; ji++) {
        Serial.print(cards[i].jobList[ji]);
        Serial.print(",");
     }
     Serial.println(" ");
   }
}

//DEBUGGING
void dumpCard(unsigned int i){
  Serial.print("Card #");
  Serial.print(i);
  Serial.print(" : ");
  Serial.print(cards[i].cardID);
  Serial.print(" : ");
  Serial.print(cards[i].currentJobIndex);
  Serial.print(" : ");
  for (int ji = 0; ji < MAX_JOBS_PER_CARD; ji++) {
    Serial.print(cards[i].jobList[ji]);
    Serial.print(",");
  }
  Serial.println(" ");
}

void updateLastCard(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
      lastCard[i] = mfrc522.uid.uidByte[i];
    }
}


void dumpByteArray(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}

/*Called like: UIDBytesIntoLong(mfrc522.uid.uidByte, mfrc522.uid.size);*/
unsigned long UIDBytesIntoLong(byte *uidBytes, byte arraySize=4){
  unsigned long id;
  unsigned long buf;
  
  id, buf = 0;
  
  for (int i=0; i<4; i++){
    buf = uidBytes[i]; // << ((3-i)*8);
    buf = buf << ((3-i)*8);
    id += buf; 
  }
 
  return id;
}

void dumpCardID(){
  unsigned long key_long;
  
  Serial.print(F("New Card UID:")); 
  dumpByteArray(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.print(F("  : ")); 
  key_long = UIDBytesIntoLong(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.print(key_long); 
  Serial.println();
}


int incrementJobIndex(unsigned long *newCardID){
  //Serial.println("Incrementing current job index for card"); 
  for (int i = 0; i < MAX_CARDS; i++) {
    if (cards[i].cardID == *newCardID){
      if (cards[i].currentJobIndex < MAX_JOBS_PER_CARD){
        cards[i].currentJobIndex++;
        return 1; 
      }
    }
  }
  return 0;
}

unsigned int getRandomJob(){
  return random(28, 45);
}

/* For Debugging Only */
void dumpAllJobStrings(){
  char buffer[JOB_STRING_LENGTH];    // make sure this is large enough for the largest string it must hold
  
  for (int i = 0; i < 6; i++){
    /* Using the string table in program memory requires the use of special functions to retrieve the data.
     The strcpy_P function copies a string from program space to a string in RAM ("buffer").
     Make sure your receiving string in RAM  is large enough to hold whatever
     you are retrieving from program space. */
    
    strcpy_P(buffer, (char*)pgm_read_word(&(jobStringTable[i])));
    Serial.println(buffer);
    delay( 50 );
    }
}

int printCurrentJobTicket(unsigned long *newCardID){
  for (int i = 0; i < MAX_CARDS; i++) {
    if (cards[i].cardID == *newCardID){
      unsigned int index = cards[i].currentJobIndex;
      unsigned int job = cards[i].jobList[index];

      //serial
      printJobString(job);

      
      
      printTicketHeader(newCardID, &index);
      
      if (index == 0) {
        printWelcomeMessage(newCardID);
      } else if (index < MAX_JOBS_PER_CARD){
        printWrappedString(&job);
      } else {
        //Print a random job
        job = getRandomJob();
        printWrappedString(&job);
      }
      return 1; //success
    }
  }
  return 0; //fail
}


int printJobString(unsigned int jobIndex){
  char buffer[JOB_STRING_LENGTH];    // make sure this is large enough for the largest string it must hold
  strcpy_P(buffer, (char*)pgm_read_word(&(jobStringTable[jobIndex])));

  Serial.print(F("Printing: "));
  Serial.println(buffer);      
  
  return 1; 
}

/* This func 'wraps' the string so it doesnt break lines on the printer */
char* word_wrap (char* buffer, char* string, int line_width) { 
    int i = 0;
    int k, counter;
 
    while(i < strlen( string ) ) {
        for ( counter = 1; counter <= line_width; counter++ ) {
            if ( i == strlen( string ) ) {
                buffer[ i ] = 0;
                return buffer;
            }
            buffer[ i ] = string[ i ];
            if ( buffer[ i ] == '\n' ){
                counter = 1; 
            }
            i++;
        }
        if ( isspace( string[ i ] ) ) {
            buffer[i] = '\n';
            i++;
        } else {
            for ( k = i; k > 0; k--) {
                if ( isspace( string[ k ] ) ) {
                    buffer[ k ] = '\n';
                    i = k + 1;
                    break;
                }
            }
        }
    }
   buffer[ i ] = 0;
 
  return buffer;
}

void printWrappedString(unsigned int *jobIndex){
  char string[JOB_STRING_LENGTH];    // make sure this is large enough for the largest string it must hold
  char buffer[JOB_STRING_LENGTH];
  
  strcpy_P(string, (char*)pgm_read_word(&(jobStringTable[*jobIndex])));
  word_wrap (buffer, string, PRINTER_LINE_WIDTH);
  
  printer.justify('L');
  printer.setSize('S');
  printer.boldOn();
  //printer.println(" ");
  //delay(2);
  printer.justify('L');
  printer.setSize('S');
  printer.println(F("################################")); //0xDB
  printer.justify('C');
  printer.println(F("INSTRUCTION START"));
  printer.justify('L');
  printer.println(F("################################")); //0xDB
  printer.println(" ");
  //delay(2);
  printer.setSize('S');
  printer.boldOn();
  printer.println(buffer);
  printer.setSize('S');
  printer.println(" ");
  printer.println(F("################################")); //0xDB
  printer.justify('C');
  printer.println(F("INSTRUCTION END"));
  printer.justify('L');
  printer.println(F("################################")); //0xDB
  printer.println("\n");
  
}

void printTicketHeader(unsigned long *currentCardID, unsigned int *currentJobIndex){ //can be rewritten as a pointer to ulong, uint
    printer.justify('L');
    printer.setSize('S');
    printer.println(F("################################")); //0xDB
    
    printer.justify('C');
    printer.setSize('S');
    printer.print(F("UID:"));
    printer.print(*currentCardID);
    printer.print(F(" JI:"));
    printer.println(*currentJobIndex);
}

void printWelcomeMessage(unsigned long *currentCardID){
  printer.justify('L');
  printer.setSize('S');
  printer.boldOn();
  //printer.println(" ");
  //delay(2);
  printer.justify('L');
  printer.setSize('S');
  printer.println(F("################################")); //0xDB
  printer.justify('C');
  printer.println(F("INSTRUCTION START"));
  printer.justify('L');
  printer.println(F("################################")); //0xDB
  printer.println(" ");
  //delay(2);
  printer.setSize('S');
  printer.boldOn();

  //Welcome to the Machine, JOHN [UID]. Prepare for group exercise.
  printer.justify('C');
  printer.println(F("Welcome to the Machine"));
  printer.justify('C');
  printer.print(F("JOHN "));
  printer.println(*currentCardID);
  printer.println(F("Prepare for group exercise"));
  printer.justify('L');
  printer.setSize('S');
  printer.println(" ");
  printer.println(F("################################")); //0xDB
  printer.justify('C');
  printer.println(F("INSTRUCTION END"));
  printer.justify('L');
  printer.println(F("################################")); //0xDB
  printer.println("\n");
  
}

void updateStatus(unsigned int new_status){
  if (status != new_status){
    status = new_status;
    dumpStatus();
    updateLCD();
  }
}

void dumpStatus(){
  char buffer[JOB_STRING_LENGTH];
    
  strcpy_P(buffer, (char*)pgm_read_word(&(statusStrings[status])));

  Serial.print(F("Status update: "));
  Serial.println(buffer);
  
}

void updateLCD(){
  delay(1);
}





