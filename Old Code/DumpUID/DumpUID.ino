
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

MFRC522::MIFARE_Key key;

byte newCard[6];
byte lastCard[] = {0,0,0,0,0,0};

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
  
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (lastCard[i] != mfrc522.uid.uidByte[i]){      
        Serial.print(F("New card : "));
        dumpByteArray(mfrc522.uid.uidByte, mfrc522.uid.size);
        Serial.println();
        updateLastCard(lastCard, mfrc522.uid.size);
    }
  }
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

void print_card_id(){
  unsigned long key_long;
  
  Serial.print(F("Card UID:")); 
  Serial.println();

  //key_long = UIDBytesIntoLong(key.keyByte
  
  
  delay(500);
}

/*Called like: UIDBytesIntoLong(mfrc522.uid.uidByte, mfrc522.uid.size);*/
unsigned long UIDBytesIntoLong(byte *uidBytes, byte arraySize=4){
  unsigned long id;
  
  for (byte i=0; i<arraySize; i++){
    id += (uidBytes[i]<<(i*8));
  }
}
