#include <lpc214x.h>
#include "types.h"
#include "lcd_defines.h"
#include "lcd.h"
#include "delays.h"
#include "function.h"
#include "kpm.h"
#include "rtc.h"
#include "password.h"
#define Intr_SW 0//@p0.0

// Globals to hold allowed device time window
u32 start_hour = 0, start_min = 0;
u32 end_hour   = 23, end_min = 59;


u32 valid_date(s32 value)
{
	if((MONTH==1)||(MONTH==3)||(MONTH==5)||(MONTH==7)||(MONTH==8)||(MONTH==10)||(MONTH==12))
	{
		if(value>=1 && value<=31)	return 1;
		else return 0;
	}
	else if((MONTH==4)||(MONTH==6)||(MONTH==9)||(MONTH==11))
	{
		if(value>=1 && value<=30)	return 1;
		else	return 0;		
	}
	else
	{
		if(MONTH==2)
		{
			if((YEAR%4)==0)
			{
				if(value>=1 && value<=29)		return 1;
				else return 0;
			}
			else{
				if(value>=1 && value<=28)		return 1;
				else return 0;
			}
		}
	}
	return 0;
}
void SetStartTime(void)
{
    s32 value,lastkey;

    CmdLCD(CLEAR_LCD);
    StrLCD("Enter Start Hr:");
    ReadNUM((u32 *)&value,(u32 *)&lastkey);
    if(value >= 0 && value <= 23) {
        start_hour = value;
    } else {
        StrLCD("Err:0-23");
        delay_s(1);
        return;
    }

    CmdLCD(CLEAR_LCD);
    StrLCD("Enter Start Min:");
     ReadNUM((u32 *)&value,(u32 *)&lastkey);
    if(value >= 0 && value <= 59) {
        start_min = value;
    } else {
        StrLCD("Err:0-59");
        delay_s(1);
        return;
    }

    StrLCD("Start Time Saved");
    delay_s(1);
}

void SetEndTime(void)
{
    s32 value,lastkey;

    CmdLCD(CLEAR_LCD);
    StrLCD("Enter End Hr:");
     ReadNUM((u32 *)&value,(u32 *)&lastkey);
    if(value >= 0 && value <= 23) {
        end_hour = value;
    } else {
        StrLCD("Err:0-23");
        delay_s(1);
        return;
    }

    CmdLCD(CLEAR_LCD);
    StrLCD("Enter End Min:");
     ReadNUM((u32 *)&value,(u32 *)&lastkey);
    if(value >= 0 && value <= 59) {
        end_min = value;
    } else {
        StrLCD("Err:0-59");
        delay_s(1);
        return;
    }

    // Validate logical window
    if((end_hour < start_hour) || 
       (end_hour == start_hour && end_min <= start_min)) {
        StrLCD("Invalid Window");
        delay_s(1);
    } else {
        StrLCD("End Time Saved");
        delay_s(1);
    }
}

void Edit_Device_Time()
	{
		u32 key;
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("EDIT DEVICE TIME");
	delay_ms(100);
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("1.START TIME");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("2.END TIME 3.EXIT");
		delay_ms(200);
	CmdLCD(CLEAR_LCD);
	key=KeyScan();
		switch(key)
		{
			case 1: SetStartTime();
			        break;
			case 2: SetEndTime(); 
			        break;

			case 3:
				      return; //forexit
			default:
				       StrLCD("Invalid Option");
	 }
}
void Edit_RTC()
{
	u32 key;
	s32 value,lastkey;
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("EDIT RTC TIME");
	delay_ms(400);
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("1.H 2.Mi 3.S 4.Dy");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("5.D 6.Mo 7.Y 8.E");
	delay_ms(500);
	key = KeyScan();
	while(ColScan()==0);
	switch(key)
		{
            case '1':  
							       CmdLCD(0x01);
							       ReadNUM((u32 *)&value,(u32 *)&lastkey);
                    if(value>=0 && value<=23) 
											SetRTCTimeInfo(value, MIN, SEC);
                    else 
											StrLCD("Err:0-23"); break;
            case '2': ReadNUM((u32 *)&value,(u32 *)&lastkey);
                    if(value>=0 && value<=59) SetRTCTimeInfo(HOUR, value, SEC);
                    else StrLCD("Err:0-59"); break;
            case '3': ReadNUM((u32 *)&value,(u32 *)&lastkey);
                    if(value>=0 && value<=59) SetRTCTimeInfo(HOUR, MIN, value);
                    else StrLCD("Err:0-59"); break;
            case '4': ReadNUM((u32 *)&value,(u32 *)&lastkey);
                    if(value>=0 && value<=6) 
											SetRTCDay(value);
                    else 
											StrLCD("Err:0-6"); break;
            case 5: ReadNUM((u32 *)&value,(u32 *)&lastkey);
                    if(valid_date(value)) 
											SetRTCDateInfo(value, MONTH, YEAR);
                    else 
											StrLCD("Invalid Date"); break;
            case 6: ReadNUM((u32 *)&value,(u32 *)&lastkey);
                    if(value>=1 && value<=12) 
											SetRTCDateInfo(DOM, value, YEAR);
                    else 
											StrLCD("Err:1-12"); break;
            case 7: ReadNUM((u32 *)&value,(u32 *)&lastkey);
                    if(value>=0 && value<=4095) 
											SetRTCDateInfo(DOM, MONTH, value);
                    else 
											StrLCD("Err:0-4095"); break;
            case 8: return; // Exit editing
     }

}
	
void open_edit_menu()
{
	u32 key;
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("Enter Password");
	delay_ms(50);

	if(Password_Check())
	{
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
	  StrLCD("SELECT TARGET");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("FOR CHANGES");
		delay_ms(400);
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
	  StrLCD("1.RTC 3.PWDCHG");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("2.DEVTIME 4.EXIT");
		delay_ms(500);
		CmdLCD(CLEAR_LCD);
		StrLCD("Enter KEY");
		key = KeyScan();
		while(ColScan()==0);
	
		switch(key)
		{
			case '1': Edit_RTC();
			        break;
			case '2': Edit_Device_Time(); 
			        break;
			case '3': Change_Password();
			        break;
			case '4':
				      return; //forexit
			default:
				       StrLCD("Invalid Option");
	 }
 }
}	

/*if(((IOPIN0>>Intr_SW)&1)==0)
{
	  open_edit_menu();
}
*/


