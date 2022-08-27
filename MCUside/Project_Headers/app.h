#include "TFC.h"

void receiveFile(char* fName);
void extractFileSize(const int msgSize);
void filesScrollMenu();
int getCurrentlyLeftSpace();
void setCurrentlyLeftSpace(int newSpace);

char *my_itoa(int num, char *str);
void put_pFile(const int argFileSize, const char* argFileName, char* argFileContent);
