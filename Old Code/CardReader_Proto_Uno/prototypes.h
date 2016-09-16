/*Prototype funcs*/

int isCardInList(unsigned long *newCardID);
int cardCmp(byte *cardID1, byte *cardID2, byte bufferSize);
void updateLastCard(byte *buffer, byte bufferSize);
unsigned long UIDBytesIntoLong(byte *uidBytes, byte arraySize);
int incrementJobIndex(unsigned long *newCardID);
unsigned int getRandomJob();

void dumpByteArray(byte *buffer, byte bufferSize);
void dumpCardList();
void dumpCard(unsigned int i);
void dumpCardID();
void dumpAllJobStrings();

char* word_wrap (char* buffer, char* string, int line_width);
int printCurrentJobTicket(unsigned long *newCardID);
void printWrappedString(unsigned int jobIndex);
void printTicketHeader(unsigned long *currentCardID, unsigned int *currentJobIndex); //rewrite
void printWelcomeMessage(unsigned long *currentCardID);

void updateStatus(unsigned int new_status);
void dumpStatus();
void updateLCD();

