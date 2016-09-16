/*Prototype funcs*/

int isCardInList(unsigned long newCardID);
int addCardToList(unsigned newCardID);
void dumpCardList();
void updateLastCard(byte *buffer, byte bufferSize);
void dumpByteArray(byte *buffer, byte bufferSize);
void printCardID();
unsigned long UIDBytesIntoLong(byte *uidBytes, byte arraySize);
int incrementJobIndex(unsigned long newCardID);
void printAllJobStrings();
int printCurrentJobString(unsigned long newCardID);
int cardCmp(byte *cardID1, byte *cardID2, byte bufferSize);
void dumpCard(unsigned int i);
void dumpCardListAsHeader();
void populateJobLists();
