#include <avr/pgmspace.h>

/* Card defines*/
#define MAX_CARDS 40
#define MAX_JOBS 40
#define MAX_JOBS_PER_CARD 10


#define NO_ID 0
#define NO_JOB 0

/*Object to store cards */
typedef struct card{
  unsigned long cardID;
  unsigned int currentJobIndex;
  //pointer to joblist
  const unsigned int *jobList;
} card; 

/* Array of cards*/
card cards[MAX_CARDS];


  
//cards[0].cardID=123123123;
//cards[0].currentJobIndex = 0;
//cards[0].jobList = jobListArray[0];
/*card new_card{
  cards[i].cardID = NO_ID;
      cards[i].currentJobIndex = 0;
      //for (int ji = 0; ji < MAX_JOBS_PER_CARD; ji++) {
        //cards[i].jobList[ji] = NO_JOB;
        cards[i].jobList = jobListArray[i];
}*/


const unsigned int jobListArray[MAX_JOBS][MAX_JOBS_PER_CARD]{
  { 1,2,3,1,1,1,1,2,3,1 },
  { 2,3,1,1,1,1,1,1,0,0 },
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

card testcard[2] = {{123123, 0, jobListArray[0]},
                  {222222, 0, jobListArray[0]}};
/* Job string defines*/
#define NUM_STRINGS 40
#define JOB_STRING_LENGTH 100

/*Object to store strings */
const char jobString0[] PROGMEM = "This is job number zero."; 
const char jobString1[] PROGMEM = "This is job number one.";
const char jobString2[] PROGMEM = "This is job number two.";
const char jobString3[] PROGMEM = "This is job number three.";
const char jobString4[] PROGMEM = "This is job number four.";
const char jobString5[] PROGMEM = "This is job number five.";

/*Array of strings*/
const char* const jobStringTable[] PROGMEM = {jobString0, jobString1, jobString2, jobString3, jobString4, jobString5};
