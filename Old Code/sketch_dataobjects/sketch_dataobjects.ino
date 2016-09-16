#include <avr/pgmspace.h>
#include "jobstrings.h"


char buffer[JOB_STRING_LENGTH];    // make sure this is large enough for the largest string it must hold

void setup()
{
  Serial.begin(9600);
  while(!Serial);
  Serial.println("OK");
}


void loop()
{
  
  printAllJobStrings();
  
}

void printAllJobStrings(){
  for (int i = 0; i < 6; i++){
    /* Using the string table in program memory requires the use of special functions to retrieve the data.
     The strcpy_P function copies a string from program space to a string in RAM ("buffer").
     Make sure your receiving string in RAM  is large enough to hold whatever
     you are retrieving from program space. */
    strcpy_P(buffer, (char*)pgm_read_word(&(jobStringTable[i])));
  
    Serial.println(buffer);
    delay( 500 );
    }
}

