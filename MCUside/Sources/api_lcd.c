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

void lcd_printFirstLine(const char* s){
	lcd_clear();
	lcd_home();
	lcd_cmd(0x6);  //Entry Mode
	lcd_cmd(0x80); //Initialize DDRAM address to zero
	lcd_puts(s);
}
void lcd_printSecondLine(const char * s){
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

void lcd_printFile(const int fileIndex){
  static int indexInFile = 0;
  char currentLineToPrint[MAX_MSG] = {0};
  int i = 0;
  
  for (i;i<MAX_MSG;i++){
    if(indexInFile < (pFiles[fileIndex].size)){  	
        currentLineToPrint[i] = (pFiles[fileIndex].content)[indexInFile++];
    }
}

  if(indexInFile >= (pFiles[fileIndex].size))
    indexInFile = 0;

  lcd_printNewLn(currentLineToPrint);
}
