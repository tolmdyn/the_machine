#include <avr/pgmspace.h>

/* Card defines*/
#define MAX_CARDS 40
#define MAX_JOBS_PER_CARD 10

/*Object to store cards */
typedef struct card{
  unsigned long cardID;
  unsigned int cardIndex;
  unsigned int *(jobList)[MAX_JOBS_PER_CARD];
} card; 

/* Array of cards*/
card cards[MAX_CARDS];

/* Data for cards */

//cards[0].cardID = 1;
//cards[0].cardIndex = 0;
//cards[0].jobList = {1,2,3,1,2,3,1,2,3,1}

//cards[1].cardId = 2;
//cards[1].cardIndex = 0;
//cards[1].jobList = {1,2,3,4,5,6,7,8,9,10}

/* JobList Arrays */
/* is an array of arrays? */
//unsigned int jobList0 = { 1,2,3,1,2,3,1,2,3,1 }
//unsigned int jobList1 = { 1,2,3,4,5,6,7,8,9,0 }

unsigned int jobListArray[40][10]{
  { 1,2,3,1,2,3,1,2,3,1 },
  { 2,2,3,1,2,3,1,2,3,1 },
  { 3,2,3,1,2,3,1,2,3,1 },
  { 4,2,3,1,2,3,1,2,3,1 },
  { 5,2,3,1,2,3,1,2,3,1 },
  { 6,2,3,1,2,3,1,2,3,1 },
  { 7,2,3,1,2,3,1,2,3,1 },
  { 8,2,3,1,2,3,1,2,3,1 },
  { 9,2,3,1,2,3,1,2,3,1 },
  { 1,1,3,1,2,3,1,2,3,1 },  
  { 1,2,3,1,2,3,1,2,3,1 },
  { 1,3,3,1,2,3,1,2,3,1 },
  { 1,4,3,1,2,3,1,2,3,1 },
  { 1,5,3,1,2,3,1,2,3,1 },
  { 1,6,3,1,2,3,1,2,3,1 },
  { 1,7,3,1,2,3,1,2,3,1 },
  { 1,8,3,1,2,3,1,2,3,1 },
  { 1,9,3,1,2,3,1,2,3,1 },
  { 1,2,3,1,2,3,1,2,3,1 },
  { 1,2,3,1,2,3,1,2,3,1 },  
  { 1,2,3,1,2,3,1,2,3,1 },
  { 1,2,3,1,2,3,1,2,3,1 },
  { 1,2,3,1,2,3,1,2,3,1 },
  { 1,2,3,1,2,3,1,2,3,1 },
  { 1,2,3,1,2,3,1,2,3,1 },
  { 1,2,3,1,2,3,1,2,3,1 },
  { 1,2,3,1,2,3,1,2,3,1 },
  { 1,2,3,1,2,3,1,2,3,1 },
  { 1,2,3,1,2,3,1,2,3,1 },
  { 1,2,3,1,2,3,1,2,3,1 },
  { 1,2,3,1,2,3,1,2,3,1 },
  { 1,2,3,1,2,3,1,2,3,1 },
  { 1,2,3,1,2,3,1,2,3,1 },
  { 1,2,3,1,2,3,1,2,3,1 },
  { 1,2,3,1,2,3,1,2,3,1 },
  { 1,2,3,1,2,3,1,2,3,1 },
  { 1,2,3,1,2,3,1,2,3,1 },
  { 1,2,3,1,2,3,1,2,3,1 },
  { 1,2,3,1,2,3,1,2,3,1 },
  { 1,2,3,1,2,3,1,2,3,1 }
};

/* Job string defines*/
#define NUM_STRINGS 40
#define JOB_STRING_LENGTH 100

/*Object to store strings */
const char jobString0[] PROGMEM = "String 0 is a string"; 
const char jobString1[] PROGMEM = "String 1 is a longer string";
const char jobString2[] PROGMEM = "String 2";
const char jobString3[] PROGMEM = "String 3 is a longer longer string";
const char jobString4[] PROGMEM = "String 4";
const char jobString5[] PROGMEM = "String 5is a longer longer is a longer longer string string";

/*Array of strings*/
const char* const jobStringTable[] PROGMEM = {jobString0, jobString1, jobString2, jobString3, jobString4, jobString5};
