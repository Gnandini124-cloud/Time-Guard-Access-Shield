#ifndef PASSWORD_H
#define PASSWORD_H
#include "types.h"

extern u32 stored_password;

u32 Password_Check(void);
void Change_Password(void);

#endif
