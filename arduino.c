#include <LPC214x.h>
#include "types.h"
#include "arduino_defines.h"
#include "arduino.h"
void pinMode(u32 pinNo,u32 pinDir)
{
  if(pinNo<32)
  {
    if(pinDir==OUTPUT)
    {
     IODIR0|=1<<pinNo;
    }
    else
    {
      IODIR0&=~(1<<pinNo);
    }
  }
  else if((pinNo>=32)&&(pinNo<=47))
  {
    if(pinDir==OUTPUT)
    {
          IODIR0|=1<<(pinNo-16);
    }
    else
    {
         IODIR1&=~(1<<pinNo);
    }
  }
}

void digitalWrite(u32 pinNo,u32 bit)
{
  if(pinNo<32)
  {
    bit? (IOSET0 = 1<<pinNo) : (IOCLR0=1<<pinNo);
  }
  else if((pinNo>=32) && (pinNo<=47))
  {
    bit?(IOSET1 = 1<<(pinNo-16)): (IOCLR1=1<<(pinNo-16));
  }
}
u32 digitalRead(u32 pinNo)
{
  u32 bit;
  if(pinNo<32)
  {
   bit=((IOPIN0>>pinNo)&1);
  }
  else if((pinNo>=32)&&(pinNo<=47))
  {
   bit=((IOPIN0>>(pinNo-16))&1);
  }
   return bit;
}
void write2pins(u32 pinStartNo,u32 nPins,u32 data)
{
   if(pinStartNo<32)
   {
    IOPIN0=((IOPIN0&~(((1<<nPins)-1)<<(pinStartNo)))|
        (data<<pinStartNo));
   }
   else if((pinStartNo>=32) && (pinStartNo<=47))
   {
    IOPIN0 = ((IOPIN0 &~(((1<<nPins)-1)<<(pinStartNo-16)))|(data<<(pinStartNo-16)));
   }
}
u32 readPins(u32 pinStartNo, u32 nPins)
{
  u32 data;
  if(pinStartNo<32)
  {
    data=((IOPIN0>>pinStartNo)&((1<<nPins)-1));
  }
  else if((pinStartNo>=32) && (pinStartNo<=47))
  {
   data=((IOPIN0>>(pinStartNo-16) &((1<<nPins)-1)));
  }
  return data;
}
void portMode(u32 pinStartNo,u32 nPins,u32 pinsDir)
{
  if(pinStartNo<32)
  {
       if(pinsDir == OUTPUT)
        {
         IODIR0 |= ((1<<nPins)-1)<<pinStartNo;
        }
        else
        {
         IODIR0&=~((1<<nPins)-1)<<pinStartNo;
        }
  }
  else if((pinStartNo>=32) && (pinStartNo<=47))
  {
      if(pinsDir==OUTPUT)
          {
       IODIR0 |= ((1<<nPins)-1)<<(pinStartNo-16);
      }
      else
      {
           IODIR0 |= ((1<<nPins)-1)<<(pinStartNo-16);
      }
   }
 }
  
