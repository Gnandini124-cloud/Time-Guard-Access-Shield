#include <lpc214x.h>
#include "function.h"
#include "password.h"
#include "types.h"
#include "rtc.h"
#include "rtc_defines.h"
#include "lcd.h"
#include "kpm.h"
#include "delays.h"
u32 FLAG;
int main()
{
	 u32 lastkey=0;
	 init_system();
	 Int_Enable();
	// Set the initial time (hours, minutes, seconds)
	  SetRTCTimeInfo(12, 14, 0);
    SetRTCDateInfo(01, 11, 2025);
    SetRTCDay(4);
	 while(1)
	 { 
		  CmdLCD(0x01); 
		  do
		  {
			   //to display current time on lcd		   && !interrupt_raised()
			    display_RTC();
				//Flag=Check_Keypress(&num,&lastkey);
		  }while(FLAG==0 && ColScan()!=0); 
			delay_ms(200);
				if(FLAG==1)
			{
				open_edit_menu();
				FLAG=0;
				continue;
			}
			CmdLCD(0x01);
	    StrLCD("Entry key..");
		  lastkey=KeyScan();
			delay_ms(200);
			while(ColScan()==0);
	    //if((Flag==1) && (lastkey=='E'))
			if(lastkey=='E')
		  {
						if(Password_Check()) 
						{
								if(permit_operation_based_on_time()) 
								{
									  CmdLCD(0x01);
										StrLCD("Access Granted");
									  delay_ms(500);
								}else {
									  CmdLCD(0x01);
										StrLCD("Access Denied");
									  delay_ms(500);
								}
						}

		  }
		
	 }

}


