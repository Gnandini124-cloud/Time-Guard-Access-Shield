#include "lcd.h"
#include "kpm.h"
#include "kpm_defines.h"
#include "lcd_defines.h"
#include "delays.h"
#include "password.h"
#include "function.h"

u32 stored_password = 1234;   

u32 Password_Check(void)
{
    u32 num=0, lastkey=0;
    CmdLCD(CLEAR_LCD);
    StrLCD("Enter Password:");
    ReadNUM(&num,&lastkey);

    if(lastkey=='E' && num==stored_password) {
        return 1;   
    } else {
			  CmdLCD(CLEAR_LCD);
        StrLCD("Wrong Password");
        delay_ms(500);
        return 0;   
    }
}


void Change_Password(void)
{
    u32 num=0, lastkey=0, new_pwd=0, confirm_pwd=0;


    CmdLCD(CLEAR_LCD);
    StrLCD("Current Password:");
    ReadNUM(&num,&lastkey);
    if(lastkey!='E' || num!=stored_password) {
        StrLCD("Wrong Password");
        delay_ms(500);
        return;
    }

 
    CmdLCD(CLEAR_LCD);
    StrLCD("New Password:");
    ReadNUM(&new_pwd,&lastkey);

    CmdLCD(CLEAR_LCD);
    StrLCD("Confirm Password:");
    ReadNUM(&confirm_pwd,&lastkey);

    if(new_pwd==confirm_pwd) {
        stored_password = new_pwd;
        StrLCD("Password Updated");
    } else {
        StrLCD("Mismatch! Try Again");
    }
    delay_ms(500);
}

