#include <avr/pgmspace.h>

/* Card defines*/
#define MAX_CARDS 40
//#define MAX_JOBS 44
//#define MAX_JOBS_PER_CARD 10
#define MAX_JOBS_PER_CARD 3

#define NO_ID   0
#define NO_JOB  0

/* Job string defines*/
#define NUM_STRINGS 40
#define JOB_STRING_LENGTH 160
//#define PRINTER_LINE_WIDTH 32
#define PRINTER_LINE_WIDTH 16

/* Status defines */
#define STATUS_NO_STATUS    255
#define STATUS_POWER_ON     0
#define STATUS_READY        1
#define STATUS_PRINTING     2
#define STATUS_TAKE_TICKET  3

/* Control card defines */
#define CONTROL_RESET_CARD      (unsigned long) 1553681371//WELCOME MESSAGE
#define CONTROL_PHASE1_CARD     (unsigned long) 479952602//JOB 1
#define CONTROL_PHASE2_CARD     (unsigned long) 741102299//JOB 2
#define CONTROL_PHASE3_CARD     (unsigned long) 741757659//RANDOM JOB (PARTY)

typedef struct card{
  unsigned long cardID;
  unsigned int currentJobIndex;
  unsigned int jobList[MAX_JOBS_PER_CARD];
} card;

/* Array of cards - this is now declared in "cards.h"*/
//card cards[MAX_CARDS];

const char statusString0[] PROGMEM = "Powering on...";
const char statusString1[] PROGMEM = "Ready. \nPlease swipe card.";
const char statusString2[] PROGMEM = "Printing\ninstructions.";
const char statusString3[] PROGMEM = "Collect your\ninstructions.";

const char* const statusStrings[] PROGMEM = {statusString0, statusString1, statusString2, statusString3};

