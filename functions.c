#include<LPC214x.h>
#include "kpm.h"
#include "kpm_defines.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "delays.h"
#include "function.h"
#include "arduino_defines.h"
#include "arduino.h"
#include "rtc.h"




void init_system()
{
	 Init_LCD();
     Init_KPM();
	 RTC_Init();
}


void ReadNUM(u32 *num,u32 *lastkey)						 //u32 *lastkey
{
 u32 key=0,i=0;
 *num=0;
 while(1)
 {
   key=KeyScan();
   if(key>='0' && key<='9')
   {
		  if(i<16)
			{
        *num=(*num*10)+(key-'0');
		    CmdLCD(GOTO_LINE2_POS0+i);
		    CharLCD(key);
				i++;
			}
		    while(ColScan()==0);
   } 
   else
   {
     *lastkey=key;
     switch(*lastkey)
     {
       case 'c': if(i>0){
				           i--;	
				           *num=(*num/10);
	                CmdLCD(GOTO_LINE2_POS0+i);
				          CharLCD(' ');
				          CmdLCD(GOTO_LINE2_POS0 + i);
			           }
	                break;
	     case 'E':  
		              return;
			 default:
				          return;
		 }
        while(ColScan()==0);
   } 
 }
}



u32 Check_Keypress(u32* num,u32* lastkey){
	 u32 key=KeyScan();
	*lastkey = key;
	 
	 if(key=='E')
	 {
		 return 1;
	 }
	 return 0;
}

u32 permit_operation_based_on_time(){
	   s32 hour,min,sec;
	   GetRTCTimeInfo(&hour,&min,&sec);
	   if(hour>=9 && hour<17)
		 {
			  return 1;
		 }
		 else{
			 return 0;
		 }
	}
	
	 

