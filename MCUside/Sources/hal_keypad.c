
#include "TFC.h"

char charOptions[16][3] = { {'1', 'G'}, // Key_0
									{'4', 'K'}, // Key_1
									{'7', 'O'}, // Key_2
									{'A', 'S'}, // Key_3
									{'2', 'H'}, // Key_4
									{'5', 'L'}, // Key_5
									{'8', 'P'}, // Key_6
									{'0', 'T'}, // Key_7
									{'3', 'I'}, // Key_8
									{'6', 'M'}, // Key_9
									{'9', 'Q'}, // Key_10
									{'B', 'W', 'X'}, // Key_11
									{'C', 'J'}, // Key_12
									{'D', 'N'}, // Key_13
									{'E', 'R'}, // Key_14
									{'F', 'Y', 'Z'} // Key_15
									};

void initKeypad() {
	// Keypad control pins:
	// PTC11: ROW1, PTC10: ROW4, PTC9: ROW7, PTC8: ROWF,
	// PTC3: COLA, PTC4: COL3, PTC5: COL2, PTC6: COL1

	// Enable clock for PORTA, PORTC and PORTD
	SIM_SCGC5 |= (SIM_SCGC5_PORTC(1));

	// Configure keypad irq port as input
	// GPIOD_PDDR &=~ 0x01;
	// PORTD_PCR0 = PORT_PCR_MUX(1);
	InitInput(Keypad_IRQ);
	setIRQType(Keypad_IRQ, INTERRUPT_ON_FALLIING_EDGE);

	// Configure ROW keypad GPIO's as output
	GPIOC_PDDR |= (ROW1 | ROW2 | ROW3 | ROW4); // PTC11, PTC10, PTC9, PTC8

	// Configure COLUMN keypad GPIO's as input
	GPIOC_PDDR &= (~COL3 & ~COL4);      // PTC4, PTC3
	GPIOC_PDDR &= (~COL1 & ~COL2);      // PTC6, PTC5

	// Confgure all Keypad pins as GPIO's. Enable pull-up on
	// column input pins
	PORTC_PCR8 = (PORT_PCR_MUX(1) | PORT_PCR_PE(0));  // PTC8
	PORTC_PCR9 = (PORT_PCR_MUX(1) | PORT_PCR_PE(0));  // PTC9
	PORTC_PCR10 = (PORT_PCR_MUX(1) | PORT_PCR_PE(0));  // PTC10
	PORTC_PCR11 = (PORT_PCR_MUX(1) | PORT_PCR_PE(0)); // PTC11

	PORTC_PCR3 = (PORT_PCR_MUX(1) | PORT_PCR_PE(1)); // PTC3
	PORTC_PCR4 = (PORT_PCR_MUX(1) | PORT_PCR_PE(1)); // PTC4
	PORTC_PCR5 = (PORT_PCR_MUX(1) | PORT_PCR_PE(1)); // PTC5
	PORTC_PCR6 = (PORT_PCR_MUX(1) | PORT_PCR_PE(1)); // PTC6
	
	memset(&keypadPressCounters, 0, sizeof(keypadPressCounters));

}

char keypad_scan(void)
{
		
		char currentlyPressedKey = 'z';
		
	
		
		GPIOC_PDOR &= (~ROW1 & ~ROW2 & ~ROW3 & ~ROW4);

		// If column pin is detected LOW, scan the column
		// to detect particular key press
		if ((GPIOC_PDIR & COL1) == 0)
			currentlyPressedKey = search_col(COL1) + 4*0;
		else if ((GPIOC_PDIR & COL2) == 0)
			currentlyPressedKey = search_col(COL2) + 4*1;
		else if ((GPIOC_PDIR & COL3) == 0)
			currentlyPressedKey = search_col(COL3) + 4*2;
		else if ((GPIOC_PDIR & COL4) == 0)
			currentlyPressedKey = search_col(COL4) + 4*3;

		GPIOC_PDOR &= (~ROW1 & ~ROW2 & ~ROW3 & ~ROW4);

		switch (currentlyPressedKey)
		{
		case 0: return pickCharacter(0);			
		case 1: return pickCharacter(1);
		case 2: return pickCharacter(2);
		case 3: return pickCharacter(3);

		case 4: return pickCharacter(4);
		case 5: return pickCharacter(5);
		case 6: return pickCharacter(6);
		case 7: return pickCharacter(7);

		case 8: return pickCharacter(8);
		case 9: return pickCharacter(9);
		case 10: return pickCharacter(10);
		case 11: return pickCharacter(11);

		case 12: return pickCharacter(12);
		case 13: return pickCharacter(13);
		case 14: return pickCharacter(14);
		case 15: return pickCharacter(15);

		default:
			return 'z';
		}
}
char pickCharacter(int idx){
	char retChar;
	if (keypadPressCounters[idx] != 0)		// If not first press, use next char option		
		lcd_cmd(0x10);						// Move cursor left
	else {
		mcuMessage[idxInMcuMessage - 1] = currentMessageChar;
		idxInMcuMessage++;					// If first-press than the character will be stored in a new index within the message sent by MCU.
	}
	if (idx != 11 && idx != 15)		
		retChar = charOptions[idx][keypadPressCounters[idx] % 2];			// For keys other than key_11 and key_15, there are 2 character options.
	else
		retChar = charOptions[idx][keypadPressCounters[idx] % 3];			// For key_11 and key_15 there are 3 character options.

	keypadPressCounters[idx]++;
	
	return retChar;
}
int search_col(uint32_t col)
{
	// Drive ROW1 output pin as LOW. Other ROW pins as HIGH
	GPIOC_PDOR &= (~ROW1);
	GPIOC_PDOR |= (ROW2 | ROW4 | ROW3);

	if ((GPIOC_PDIR & col) == 0)
		return 0;

	// Drive ROW2 output pin as LOW. Other ROW pins as HIGH
	GPIOC_PDOR &= (~ROW2);
	GPIOC_PDOR |= (ROW1 | ROW3 | ROW4);

	if ((GPIOC_PDIR & col) == 0)
		return 1;

	// Drive ROW3 output pin as LOW. Other ROW pins as HIGH
	GPIOC_PDOR &= (~ROW3);
	GPIOC_PDOR |= (ROW1 | ROW2 | ROW4);

	if ((GPIOC_PDIR & col) == 0)
		return 2;

	// Drive ROW4 output pin as LOW. Other ROW pins as HIGH
	GPIOC_PDOR &= (~ROW4);
	GPIOC_PDOR |= (ROW1 | ROW2 | ROW3);

	if ((GPIOC_PDIR & col) == 0)
		return 3;

	return -16;
}
