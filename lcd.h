#ifndef __LCD_H__
#define __LCD_H__
#include "types.h"

void Init_LCD(void);
void CmdLCD(u8 cmdByte);
void Write(u8 byte);
void StrLCD(s8 *);
void F32LCD(f32,u32);
void BuildCGRAM(cu8 *,u8);
void S32LCD(s32);
void U32LCD(u32);
void CharLCD(u8);

#endif

