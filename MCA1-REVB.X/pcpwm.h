#include <xc.h>

#define IR2110_ENABLE   PORTDbits.RD7

void InitPCPWM(void);
void SetPWM1Duty(unsigned int);
void SetPWM2Duty(unsigned int);
void IR2110Enable(void);
void IR2110Disable(void);
