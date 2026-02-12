#include "types.h"
#define sw1 0//p0.0
void init_system(void);
void ReadNUM(u32 *,u32 *);
u32 interrupt_raised(void);
u32 Check_Keypress(u32*,u32*);
u32 permit_operation_based_on_time(void);
void open_edit_menu(void);
void Int_Enable(void);
