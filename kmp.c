#include "types.h"
#include "kpm_defines.h"
#include "lcd_defines.h"
#include "lcd.h"
#include "kpm.h"
#include<LPC214x.h>
//u32 kmpLUT[4][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
u32 kmpLUT[4][4]={
                  {'7','8','9','A'},
                  {'4','5','6','B'},
                  {'1','2','3','C'},
                  {'c','0','E','D'} 
				 };

void Init_KPM(void)
{
 //rows output and ground
 IODIR1|=15<<ROW0; //4pins
 //cols input and high by default
}

u32 ColScan(void)
{
  u32 status;
  status = (((IOPIN1>>COL0)&15)<15)?0:1;
  return status;
  }

u32 RowCheck(void)
{
 u32 r;
 for(r=0;r<=3;r++)
 {
  //starting with row0,upto row3
  IOPIN1=((IOPIN1&~(15<<ROW0))|((~(1<<r))<<ROW0));
  //check if key was pressed in that row
  if(ColScan()==0)
  {
   break;
  }
  }
  //re-intialize rows to their state
   IOCLR1|=15<<ROW0;
 //IOPIN1=((IOPIN1&~(15<<ROW0))|(0<<ROW0));
  return r;
 }

u32 ColCheck(void)
{
 u32 C;
 for(C=0;C<=3;C++)
 {
  //starting with col0 upto col3
  //check one col at a time for low
  if(((IOPIN1>>(COL0+C))&1)==0)
  {
    break;
  }
 }
 return C;
}

u32 KeyScan(void)
{
 u32 r,C,keyV;
 //Initialize kpm
 Init_KPM();
 //wait for the key press detection
 while(ColScan());
 //identify row in which key was pressed
 r=RowCheck();
 //identify col in which key was pressed
 C=ColCheck();
 //extract key value from LUT
 keyV=kmpLUT[r][C];
 return keyV;
}
void ReadNum(u32 *num,u32 *lastkey)
{
 u32 key;
 *num=0;
 while(1)
 {
   key=KeyScan();
   if(key>='0' && key<='9')
   {
        *num=(*num*10)+(key-'0');
		while(ColScan()==0);
   }
   else
   {
   *lastkey=key;
   while(ColScan()==0);
   break;
   }
 }
}


