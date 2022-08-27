#include "app.h"

#include <stdio.h>

#include <stdlib.h>

#define BUFFER_SIZE 10

int currentlyLeftSpace;

int getCurrentlyLeftSpace() {
  return currentlyLeftSpace;
}

void setCurrentlyLeftSpace(int newSpace) {
  currentlyLeftSpace = newSpace;
}


void receiveFile(char * fName) {
	
	if(currentFileSize < getCurrentlyLeftSpace())	// File can be pushed into the array w/o overflowing
		put_pFile(currentFileSize, fName, tempFile2);
	
	else if (fileCount && currentFileSize < (getCurrentlyLeftSpace() - pFiles[fileCount - 1].size)){
		free(pFiles[fileCount - 1].content);
		setCurrentlyLeftSpace( getCurrentlyLeftSpace() + pFiles[fileCount - 1].size);
		put_pFile(currentFileSize, fName, tempFile2);
	}
}

void extractFileSize(const int msgSize) {
  int i;
  char tempFileSize[4] = {
    0
  };

  for (i = 0; i < 4; i++) {
    tempFileSize[i] = message[i + msgSize - 4];
    message[i + msgSize - 4] = i == 0 ? ' ' : '\0';
  }

  currentFileSize = atoi(tempFileSize);
  
  if ((fileCount > 0) && (currentFileSize > (getCurrentlyLeftSpace() - pFiles[fileCount - 1].size)))
	  ableToReceiveFile = 0;
  else
	  ableToReceiveFile = 1;
	  
}

void filesScrollMenu() {

  static int scrollCounter = 0;

  int firstFileIndex = scrollCounter;
  currentPointedFileIndex = firstFileIndex;

  scrollCounter = (++scrollCounter) % (fileCount);
  int secondFileIndex = scrollCounter;

  char str1[6];
  my_itoa(pFiles[firstFileIndex].size, str1);
  strcat(str1, "B\0");

  char str2[6];
  my_itoa(pFiles[secondFileIndex].size, str2);
  strcat(str2, "B\0");

  char firstFileName[MAX_LINE];
  char secondFileName[MAX_LINE];

  strcpy(firstFileName, pFiles[firstFileIndex].name);
  strcat(firstFileName, str1);

  strcpy(secondFileName, pFiles[secondFileIndex].name);
  strcat(secondFileName, str2);

  int len1 = strlen(firstFileName);
  int len2 = strlen(secondFileName);
  lcd_printFirstLine(firstFileName);
  lcd_printSecondLine(secondFileName);
}

char * my_itoa(const int num, char * str) {
  if (str == NULL) {
    return NULL;
  }
  sprintf(str, "%d", num);
  return str;
}

void put_pFile(const int argFileSize, const char* argFileName, char* argFileContent){
	int i;
	if(fileCount){
		for (i = fileCount - 1; i >= 0; i--)
			pFiles[i+1] = pFiles[i];
	}
	pFiles[0].size = argFileSize;
	
	strcpy(pFiles[0].name, argFileName);
	pFiles[0].name[strlen(argFileName)] = '\0';
	
	argFileContent[0] = receivedByte; // Last received byte should be the first byte of the file.
	pFiles[0].content = argFileContent;
	pFiles[0].content[argFileSize] = '\0';
	fileCount++;
	setCurrentlyLeftSpace(getCurrentlyLeftSpace() - argFileSize);
}
