#include<LPC21xx.h>
#include "Types.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "pin_function_defines.h"
#include "pin_connect_block.h"
#include "function.h"
#include "delays.h"

#define EINT0_VIC_CHN0 14
#define EINT0_STATUS_LED 16
#define EINT0_PIN0_0_1 PIN_FUNC4
void eint0_isr(void) __irq;
extern u32 FLAG;
u32 gCount;
void Int_Enable(void)
{
 //cfg EINT0 STATUS led pin as gpio output
 //IODIR1|=1<<EINT0_STATUS_LED;
 //cfg p0.1 pin as EINT0 input pin
// CfgPinFunc(0,1,EINT0_PIN0_0_1);
	  PINSEL0 |= (3 << 2);
	EXTMODE|=(1<<0);
	EXTPOLAR&=~(1<<0);
 //cfg VIC peripherals for EINT0
	EXTINT=1<<0;
 //cfg  EINT0 as irq type,def all are anyway irq
 VICIntSelect=0;
 //enable EINT0 via VIC
 VICIntEnable = 1<<EINT0_VIC_CHN0;
 //cfg EINT0 as Virq,highest priority 0
 VICVectCntl0 =(1<<5) | EINT0_VIC_CHN0;
 //Cfg EINT0 as virq ,highest priority 0
 //load eint0_isr addr in handware lut sfr for virq
 VICVectAddr0=(u32)eint0_isr;
 //cfgexternal interrupt peripheral
 //enable EINTO,def all eints are any enable
 //EXTINT=0;
 //cfg EINT0 for edge are any enable
 //EXTMODE=1<<0;
 //cfg EINT0 for falling edge triggering,def  FE anyway
 //EXTPOLAR=0
 //enter regular operations
}
void eint0_isr(void) __irq
{
  //eint0 isr user activity begins
  //toggle EINT0 status led upon interrupt fired/raised
  //IOPIN1^=1<<EINT0_STATUS_LED;
	FLAG=1;

  //einto isr user activity ends
  //clear eint0 status in external interrupt peripheral
  EXTINT=1<<0;
  //clear EINT0 status in VIC peripheral
  VICVectAddr=0;
}
