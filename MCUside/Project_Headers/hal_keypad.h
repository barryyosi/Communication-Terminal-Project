/**************************************************
* @file:     Keypad.h
* @revision: 1.0
* @date:     09-Dec-2018
* @brief:    Keypad global data definition
***************************************************/

#ifndef _KEYPAD_H
#define _KEYPAD_H

#include "TFC.h"
/**************************************************
Constants
***************************************************/
typedef enum
{
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	NO_OF_KEYS,
}key_enm;


/**************************************************
Global Function Prototypes
***************************************************/

#define ROW1  ((uint32_t)1 << 11)  // PTC11
#define ROW2  ((uint32_t)1 << 10)  // PTC10
#define ROW3  ((uint32_t)1 << 9)   // PTC9
#define ROW4  ((uint32_t)1 << 8)   // PTC8

#define COL4   ((uint32_t)1 << 3)  // PTC3
#define COL3   ((uint32_t)1 << 4)  // PTC4
#define COL2   ((uint32_t)1 << 5)  // PTC5
#define COL1   ((uint32_t)1 << 6)  // PTC6

void initKeypad();
char keypad_scan(void);
char pickCharacter(int idx);
int search_col(uint32_t col);

#endif  // end of _KEYPAD_H