
#ifndef APP_FSM_H_
#define APP_FSM_H_


typedef enum {sleepMode, chatMode, fileTransferMode, terminalConfigMode} FSMstate;


void handleStateChangeIfNeeded();
void enterState(FSMstate state);
void exitState(FSMstate state);

void updateState(FSMstate argState);
void setState(FSMstate argState);
FSMstate getState();

int getX();
void setX(int newX);

int getUpCountAndInc();
int getDownCountAndDecr();

void resetUpCount();
void resetDownCount();


#endif