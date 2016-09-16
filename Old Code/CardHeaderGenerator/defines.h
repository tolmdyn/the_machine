#include <avr/pgmspace.h>

/* Card defines*/
#define MAX_CARDS 40
#define MAX_JOBS 40
#define MAX_JOBS_PER_CARD 10


#define NO_ID 0
#define NO_JOB 0


/*Object to store cards */
/*typedef struct dummycard{
  unsigned long cardID;
  unsigned int currentJobIndex;
  //pointer to joblist
  const unsigned int *jobList;
} dummycard; 
*/
/* Array of cards*/
/*dummycard dummycards[MAX_CARDS];*/

/*Object to store cards */
/*typedef struct card{
  unsigned long cardID;
  unsigned int currentJobIndex;
  //pointer to joblist
  //const unsigned int *jobList;
  unsigned int jobList[MAX_JOBS_PER_CARD];
} card; 
*/

//modified to save mem
typedef struct card{
  unsigned long cardID;
  unsigned int currentJobIndex;
  //pointer to joblist
  //const unsigned int *jobList;
  //unsigned int jobList[MAX_JOBS_PER_CARD];
} card;


/* Array of cards*/
card cards[MAX_CARDS];

/* Job string defines*/
#define NUM_STRINGS 40
#define JOB_STRING_LENGTH 100


