#include <avr/pgmspace.h>

/* Card defines*/
#define MAX_CARDS 40
#define MAX_JOBS 40
//#define MAX_JOBS_PER_CARD 10
#define MAX_JOBS_PER_CARD 3

#define NO_ID   0
#define NO_JOB  0

/* Job string defines*/
#define NUM_STRINGS 40
#define JOB_STRING_LENGTH 100
#define PRINTER_LINE_WIDTH 32

/* Status defines */
#define STATUS_POWER_ON     0
#define STATUS_READY        1
#define STATUS_PRINTING     2
#define STATUS_TAKE_TICKET  3

typedef struct card{
  unsigned long cardID;
  unsigned int currentJobIndex;
  unsigned int jobList[MAX_JOBS_PER_CARD];
} card;

/* Array of cards - this is now declared in "cards.h"*/
//card cards[MAX_CARDS];

const char statusString0[] PROGMEM = "Powering on...";
const char statusString1[] PROGMEM = "Ready. Please swipe card.";
const char statusString2[] PROGMEM = "Printing instructions. Please wait";
const char statusString3[] PROGMEM = "Please collect your instructions.";

const char* const statusStrings[] PROGMEM = {statusString0, statusString1, statusString2, statusString3};

