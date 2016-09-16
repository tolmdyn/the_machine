#include <SPI.h>
#include <MFRC522.h>

#include "data.h"
#include "prototypes.h"

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

MFRC522::MIFARE_Key key;

//byte newCard[6];
byte lastCard[] = {0,0,0,0,0,0};



unsigned long newCardID;

long lastUidRead;


void setup() {
	Serial.begin(9600);		// Initialize serial communications with the PC
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  //Initialise Cards
  for (int i = 0; i < MAX_CARDS; i++) {
      cards[i].cardID = NO_ID;
      cards[i].currentJobIndex = 0;
      //for (int ji = 0; ji < MAX_JOBS_PER_CARD; ji++) {
        //cards[i].jobList[ji] = NO_JOB;
        cards[i].jobList = jobListArray[i];
     //}
   }

  /* Data for cards */
  /*cards[0].cardID = 1;
  cards[0].currentJobIndex = 0;
  cards[0].jobList[0] = 1;
  cards[0].jobList[1] = 2;*/
  
  //cards[1].cardID = 2;
  //cards[1].currentJobIndex = 0;
  //cards[1].jobList[] = {1,2,3,4,5,6,7,8,9,10}
  dumpCardList();
  printAllJobStrings();

  lastUidRead = 0;
   
 }

void loop() {
	// Look for new cards
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
    delay(50);
	}
  
    
    //if (!cardCmp(mfrc522.uid.uidByte, lastCard, mfrc522.uid.size)){
    if ((millis()-lastUidRead) > 2000) {
        printCardID(); 
        updateLastCard(lastCard, mfrc522.uid.size);

        newCardID = UIDBytesIntoLong(mfrc522.uid.uidByte, mfrc522.uid.size);  
        
        if (!isCardInList(newCardID)){
          //If it isnt in list add it
          addCardToList(newCardID);
          dumpCardList();
        } else {
          //Increment number of times swiped
          incrementJobIndex(newCardID);
          printCurrentJobString(newCardID);
          //dumpCardList();
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
/*
int cardCmp(unsigned long cardID1, unsigned long cardID2){
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (lastCard[i] != mfrc522.uid.uidByte[i]){
      return 0; //is not equal
    }
  }
  return 1; //is equal
}*/

int isCardInList(unsigned long newCardID){
  //compared unsigned long to each element in list
  for (int i = 0; i < MAX_CARDS; i++) {
     if (cards[i].cardID == newCardID){
      Serial.println("is in list");
      return 1; //is in list
     }
  }
  Serial.println("not in list");
  return 0; //is not in list
}

int addCardToList(unsigned long newCardID){
  Serial.println("Adding entry to list:"); 
  //Serial.print(key_long); 
  for (int i = 0; i < MAX_CARDS; i++) {
    if (cards[i].cardID == NO_ID){
      cards[i].cardID = newCardID;
      return 1; 
    }
  }
  return 0;
}

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

void printCardID(){
  unsigned long key_long;
  
  Serial.print(F("New Card UID:")); 
  dumpByteArray(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.print(F("  : ")); 
  key_long = UIDBytesIntoLong(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.print(key_long); 
  Serial.println();
  delay(500);
}

int incrementJobIndex(unsigned long newCardID){
  Serial.println("Incrementing current job index for card"); 
  //Serial.print(key_long); 
  for (int i = 0; i < MAX_CARDS; i++) {
    if (cards[i].cardID == newCardID){
      if (cards[i].currentJobIndex < MAX_JOBS_PER_CARD){
        cards[i].currentJobIndex++;
        return 1; 
      }
    }
  }
  return 0;
}

void printAllJobStrings(){
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

int printCurrentJobString(unsigned long newCardID){
  char buffer[JOB_STRING_LENGTH];    // make sure this is large enough for the largest string it must hold
  unsigned int jobIndex;
  
  for (int i = 0; i < MAX_CARDS; i++) {
    if (cards[i].cardID == newCardID){
        //Serial.println(cards[i].currentJobIndex);
        //Serial.println(cards[i].jobList[cards[i].currentJobIndex]);
        jobIndex = cards[i].jobList[cards[i].currentJobIndex];       
        strcpy_P(buffer, (char*)pgm_read_word(&(jobStringTable[jobIndex])));
        Serial.println(buffer);      
        return 1; 
      
    }
  }
  Serial.print("printCurrentJobString Fail");
  return 0;
}

