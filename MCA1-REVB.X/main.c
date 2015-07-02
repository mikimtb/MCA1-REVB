#define _XTAL_FREQ 40000000

#include <xc.h>

#define Y   89
#define N   78

// Project config for PIC18F4431
#pragma config OSC = HSPLL      // Oscillator Selection bits (HS oscillator, PLL enabled (clock frequency = 4 x FOSC1))
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)
#pragma config IESO = ON        // Internal External Oscillator Switchover bit (Internal External Switchover mode enabled)
#pragma config PWRTEN = ON      // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bits (Brown-out Reset disabled)
#pragma config WDTEN = OFF      // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDPS = 32768     // Watchdog Timer Postscale Select bits (1:32768)
#pragma config WINEN = OFF      // Watchdog Timer Window Enable bit (WDT window disabled)
#pragma config PWMPIN = OFF     // PWM output pins Reset state control (PWM outputs disabled upon Reset (default))
#pragma config LPOL = HIGH      // Low-Side Transistors Polarity (PWM0, 2, 4 and 6 are active-high)
#pragma config HPOL = HIGH      // High-Side Transistors Polarity (PWM1, 3, 5 and 7 are active-high)
#pragma config T1OSCMX = ON     // Timer1 Oscillator MUX (Low-power Timer1 operation when microcontroller is in Sleep mode)
#pragma config FLTAMX = RC1     // FLTA MUX bit (FLTA input is multiplexed with RC1)
#pragma config SSPMX = RD1      // SSP I/O MUX bit (SCK/SCL clocks and SDA/SDI data are multiplexed with RD3 and RD2, respectively. SDO output is multiplexed with RD1.)
#pragma config PWM4MX = RB5     // PWM4 MUX bit (PWM4 output is multiplexed with RB5)
#pragma config EXCLKMX = RC3    // TMR0/T5CKI External clock MUX bit (TMR0/T5CKI external clock input is multiplexed with RC3)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (Enabled)
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Low-Voltage ICSP Enable bit (Low-voltage ICSP disabled)
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000200-000FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (001000-001FFF) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (002000-002FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (003000-003FFFh) not code-protected)
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot Block (000000-0001FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000200-000FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (001000-001FFF) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (002000-002FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (003000-003FFFh) not write-protected)
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0001FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000200-000FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (001000-001FFF) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (002000-002FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (003000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0001FFh) not protected from table reads executed in other blocks)
// End of project config for PIC18F4431

#include "uart.h"
#include "input.h"
#include "dc_brake.h"
#include "pcpwm.h"
#include "qei.h"
#include "comm_protocol.h"

const char fVersion[] = "v1.0";
comm_package in = {120, 0, {{0}, 0, 0}, 0};
comm_package out = {130, 0, {{0}, 0, 0}, 0};


void interrupt low_priority LowIsr(void)
{
    if (PIR1bits.RCIF && PIE1bits.RCIE)                                         // UART Receive interrupt
    {
        unsigned char a = RCREG;
        //BufferWrite(a, &in);
    }
}

void interrupt HighIsr(void)
{
    
}

/**
 * Delay in milliseconds
 * @param delay - unsigned integer in range of 0 - 65535
 */
void delay_ms(unsigned int delay)
{
    int i; 
    for (i = 0; i < delay; i++)
        __delay_ms(1);
}

int main() 
{
    //unsigned char array[2];
    UARTInit(921600);
    UARTAddressDetection_OFF();
    
    // Initialize C1 and C2 inputs
    InputInit();
    
    //Initialize DC Brake PWM generator
    DCBrake_PWMInit();
    
    SetDCBrake_NominalVoltage(24, 26);
    DCBrake_Catch();
    
    InitPCPWM();
    SetPWM1Duty(1023);
    SetPWM2Duty(1023);
    IR2110Disable();
    
    InitQEI(VELOCITY_MODE_DISABLE | QEI_4X_RESET_ON_MAXCNT | VELOCITY_POSTCALER_1, T5CKI_FILTER_DISABLE, 255);
    
    Package_AddData(&in, fVersion[0]);
    Package_AddData(&in, fVersion[1]);
    Package_AddData(&in, fVersion[2]);
    Package_AddData(&in, fVersion[3]);
    
    Package_Send(&in);
    
    delay_ms(100);
    
    Package_AddData(&out, fVersion[0]);
    Package_AddData(&out, fVersion[1]);
    
    Package_Send(&out);
    
    RCONbits.IPEN = 1;                                                          // Interrupts priority enabled
    INTCONbits.GIEH = 1;                                                        // Enable All High Priority Interrupts
    INTCONbits.GIEL = 1;                                                        // Enable All Low Priority Interrupts

    delay_ms(1);
    
    while (1)
    {
        

    }
    
    return 0;
}

