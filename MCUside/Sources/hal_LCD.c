
#include "TFC.h"
#include "MKL25Z4.h"
#include "bsp_gpio.h"
#include "hal_LCD.h"

//******************************************************************
// send a command to the LCD
//******************************************************************

//******************************************************************
// send data to the LCD
//******************************************************************
void lcd_putchar(unsigned char c){

	LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h

	LCD_DATA_WRITE &= ~OUTPUT_DATA;
	LCD_RS(1);
	if (LCD_MODE == FOURBIT_MODE)
	{
		lcd_SetOutPut4bit(((c >> 4) & 0x0F) << LCD_DATA_OFFSET);
		LCD_DATA_WRITE &= (0xF0 << LCD_DATA_OFFSET) | (0xF0 >> (8 - LCD_DATA_OFFSET));
		lcd_SetOutPut4bit((c & (0x0F)) << LCD_DATA_OFFSET);
	}

	LCD_RS(0);
}
		

//******************************************************************
// initialize the LCD
//******************************************************************

void initLCD(){

	char init_value;

	if (LCD_MODE == FOURBIT_MODE) init_value = 0x3 << LCD_DATA_OFFSET;
        else init_value = 0x3F;

	initLCD_pins();

	DelayMs(15);
	lcd_SetOutPut4bit(init_value);
	DelayMs(5);
	lcd_SetOutPut4bit(init_value);
	DelayUs(200);
	lcd_SetOutPut4bit(init_value);

	if (LCD_MODE == FOURBIT_MODE){
		LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h
		lcd_SetOutPut4bit(0x2 << LCD_DATA_OFFSET);
		lcd_cmd(0x28); // Function Set
	}

	cursorBlink();  //Display On, Cursor On, Cursor Blink
	lcd_clear();  //Display Clear
	setEntryMode();
	lcd_goto_start(); //Initialize DDRAM address to zero
}


////////////////////////////////////////////////////////////////////////////////


void initLCD_pins(){
	int lcd_pin;
	for(lcd_pin = 0; lcd_pin< 7; lcd_pin++){
		initOutput(lcdPorts[lcd_pin]);
	}
}

void lcd_strobe(){
  LCD_EN(1);
  asm("nop");
  asm("nop");
  LCD_EN(0);

}

void lcd_SetOutPut4bit(unsigned char c){
	LCD_DATA_WRITE &= ~OUTPUT_DATA;// clear bits before new write
	LCD_DATA_WRITE |= c;
	lcd_strobe();
}

void lcd_cmd(unsigned char c){

	LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h

	if (LCD_MODE == FOURBIT_MODE)
	{
		lcd_SetOutPut4bit(((c >> 4) & 0x0F) << LCD_DATA_OFFSET);
		lcd_SetOutPut4bit((c & (0x0F)) << LCD_DATA_OFFSET);
	}
}
