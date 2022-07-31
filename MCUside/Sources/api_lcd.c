#include "hal_LCD.h"

#define MAX_LCD_LEN 16

void lcd_printInt(int number){

	char pNumber[MAX_LCD_LEN];
	sprintf(pNumber, "%d", number);
	lcd_printNewLn(pNumber);

}

void lcd_printNewLn(const char * s){
	lcd_clear();
	lcd_home();
	lcd_cmd(0x6);  //Entry Mode
	lcd_cmd(0x80); //Initialize DDRAM address to zero
	lcd_puts2(s);
}

void lcd_printLine2(const char * s){
    lcd_go_to_line2();
	lcd_puts(s);
}
void lcd_puts2(const char * s){
	int idx = 0;
	while(*s){
		lcd_putchar(*s++);
		idx++;
		if(idx == MAX_LCD_LEN - 1)
			lcd_cmd(0xC0);
		
		
	}
}

void lcd_puts(const char * s){
	while(*s)
		lcd_putchar(*s++);
}

void lcd_putchar2(unsigned char c){
	if (idxInMcuMessage == MAX_LCD_LEN - 4)		// Cursor reached end of line
		lcd_cmd(0xC0);		// Move cursor one line down.
	lcd_putchar(c);
		
}
