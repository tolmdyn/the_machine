#include <Adafruit_Thermal.h>
#include <SPI.h>
#include <avr/pgmspace.h>

/* For Word Wrap */
#include <string.h>
#include <ctype.h>


#include "SoftwareSerial.h"   // for printer
#define TX_PIN 6 // Arduino pin 6 for  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino pin 5 for   GREEN WIRE   labeled TX on printer

#include "jobStrings.h"

/* Job string defines*/
#define NUM_STRINGS 40
#define JOB_STRING_LENGTH 100

/* Printer Biz */
SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

void setup() {
  Serial.begin(9600);    // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

  SPI.begin();               // Init SPI bus 
  pinMode(TX_PIN, OUTPUT);
  pinMode(RX_PIN, OUTPUT);

  pinMode(7, OUTPUT); digitalWrite(7, LOW);

  // NOTE: SOME PRINTERS NEED 9600 BAUD instead of 19200, check test page.
  mySerial.begin(19200);  // Initialize SoftwareSerial
  //Serial1.begin(19200); // Use this instead if using hardware serial
  printer.begin();        // Init printer (same regardless of serial type)
  Serial.println("begin");
  printer.println("Reset");

  printTicketHeader(2657528197,0);
  printWrappedString(0);
  printTicketHeader(2657528197,3);
  printWrappedString(3);
  
}

void loop() {
  while(1){
    delay(100);
  }
}


int printJobString(unsigned int jobIndex){
  char buffer[JOB_STRING_LENGTH];    // make sure this is large enough for the largest string it must hold
  strcpy_P(buffer, (char*)pgm_read_word(&(jobStringTable[jobIndex])));
  Serial.println(buffer);      
  
  return 1; 
}

#define BUFFER_SIZE 16

void printWrappedJobString(unsigned int jobIndex) {
  char buffer[160];    // make sure this is large enough for the largest string it must hold
  strcpy_P(buffer, (char*)pgm_read_word(&(jobStringTable[jobIndex])));
  
  Serial.println("#################");
  Serial.print("Unformatted string:");
  Serial.println(buffer);
  
  size_t string_length = strlen(buffer);
  Serial.println(string_length);
  Serial.println("");
  

  for (unsigned int i = 1; i <= string_length ; i++) { 
    if ((i % BUFFER_SIZE) == 0) { 
      int spaceCount = 0; 
      if (buffer[(i-1)] != ' ') { 
        for (int j = (i-1); j >-1 ; j--){
          if (buffer[j] == ' '){
            buffer[j]='\n';
            //s.insert(j, spaceCount, ‘ ‘);
            break;
          }
          else spaceCount++;
        }
      }
    }
  }
 
  Serial.println(buffer);
  //printer.setSize('L');
  //printer.println("#################");
  //printer.println(buffer);
  //printer.println("#################");
  Serial.println("#################");
 }


void printWrappedJobStringTicket(unsigned int jobIndex) {
  char buffer[160];    // make sure this is large enough for the largest string it must hold
  strcpy_P(buffer, (char*)pgm_read_word(&(jobStringTable[jobIndex])));
  size_t string_length = strlen(buffer);
  
  /*
  Serial.println("#################");
  Serial.print("Unformatted string:");
  Serial.println(buffer);

  Serial.println(string_length);
  Serial.println("");
  */

  for (unsigned int i = 1; i <= string_length ; i++) { 
    if ((i % BUFFER_SIZE) == 0) { 
      int spaceCount = 0; 
      if (buffer[(i-1)] != ' ') { 
        for (int j = (i-1); j >-1 ; j--){
          if (buffer[j] == ' '){
            buffer[j]='\n';
            //s.insert(j, spaceCount, ‘ ‘);
            break;
          }
          else spaceCount++;
        }
      }
    }
  }

  Serial.println("#################"); 
  Serial.println(buffer);
  Serial.println("#################");
  
  printer.println(" ");
  printer.justify('L');
  printer.setSize('L');
  printer.println(" ");
  printer.println("#################");
  printer.println(" ");
  printer.setSize('L');
  printer.println(buffer);
  printer.setSize('L');
  printer.println(" ");
  printer.println("#################");
 }

void printTicketHeader(unsigned long currentCardID, unsigned int currentJobIndex){ //can be a pointer to ulong, uint
    printer.justify('L');
    printer.setSize('S');
    printer.println(F("################################")); //0xDB
    
    printer.justify('C');
    printer.setSize('S');
    printer.print(F("UID:"));
    printer.print(currentCardID);
    printer.print(F(" JI:"));
    printer.println(currentJobIndex);
}

/*
   This function takes a string and an output buffer and a desired width. It then copies 
   the string to the buffer, inserting a new line character when a certain line
   length is reached.  If the end of the line is in the middle of a word, it will
   backtrack along the string until white space is found.
 */
 
char* word_wrap (char* buffer, char* string, int line_width) {
    int i = 0;
    int k, counter;
 
    while(i < strlen( string ) ) {
        // copy string until the end of the line is reached
        for ( counter = 1; counter <= line_width; counter++ ) {
            // check if end of string reached
            if ( i == strlen( string ) ) {
                buffer[ i ] = 0;
                return buffer;
            }
            buffer[ i ] = string[ i ];
            // check for newlines embedded in the original input 
            // and reset the index
            if ( buffer[ i ] == '\n' ){
                counter = 1; 
            }
            i++;
        }
        // check for whitespace
        if ( isspace( string[ i ] ) ) {
            buffer[i] = '\n';
            i++;
        } else {
            // check for nearest whitespace back in string
            for ( k = i; k > 0; k--) {
                if ( isspace( string[ k ] ) ) {
                    buffer[ k ] = '\n';
                    // set string index back to character after this one
                    i = k + 1;
                    break;
                }
            }
        }
    }
    buffer[ i ] = 0;
 
  return buffer;
}


void printWrappedString(unsigned int jobIndex){
  //char buffer[JOB_STRING_LENGTH];
  char string[160];    // make sure this is large enough for the largest string it must hold
  strcpy_P(string, (char*)pgm_read_word(&(jobStringTable[jobIndex])));

  char buffer[160];
  
  word_wrap (buffer, string, 32);
  
  Serial.println("#### THIS ####"); 
  Serial.println(buffer);
  Serial.println("#### ISIT ####");
  
  //printer.println(" ");
  
  printer.justify('L');
  printer.setSize('S');
  printer.boldOn();
  delay(2);
  printer.justify('L');
  printer.setSize('S');
  printer.println(F("################################")); //0xDB
  printer.justify('C');
  printer.println(F("INSTRUCTION START"));
  printer.justify('L');
  printer.println(F("################################")); //0xDB
  printer.println(" ");
  delay(2);
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

