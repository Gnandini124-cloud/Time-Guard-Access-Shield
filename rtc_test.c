#include <LPC21xx.H>

#include "lcd.h"
#include "lcd_defines.h"
#include "types.h"

#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)
#define PREINT_VAL ((PCLK/32768)-1)
#define PREFRAC_VAL (PCLK - ((PREINT_VAL+1)*32768))


s8 week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};

int main()
{
	//reset clock tick counter using CCR 
	CCR = 1<<1;
	//set 1 second tick rate
	//PREINT = PREINT_VAL;
	//PREFRAC = PREFRAC_VAL;
	//enable the clock
	CCR = 1<<0 | 1<<4;
	
	
	Init_LCD();
	
	HOUR = 16;
	MIN = 46;
	SEC = 0;
	DOM = 24;
	MONTH = 11;
	YEAR = 2025;
	DOW = 1;
	
	
	while(1)
	{
		CmdLCD(GOTO_LINE1_POS0);
		CharLCD((HOUR/10)+48);
		CharLCD((HOUR%10)+48);
		CharLCD(':');
		CharLCD((MIN/10)+48);
		CharLCD((MIN%10)+48);
		CharLCD(':');
		CharLCD((SEC/10)+48);
		CharLCD((SEC%10)+48);
		
		CmdLCD(GOTO_LINE1_POS0+10);
		StrLCD(week[DOW]);
		
		CmdLCD(GOTO_LINE2_POS0);
		CharLCD((DOM/10)+48);
		CharLCD((DOM%10)+48);
		CharLCD('/');
		CharLCD((MONTH/10)+48);
		CharLCD((MONTH%10)+48);
		CharLCD('/');
		U32LCD(YEAR);
	
		
	}
}
