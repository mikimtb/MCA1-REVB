#include <xc.h>
#include "pcpwm.h"
/**
 * Power Control PWM Initialisation
 */
void InitPCPWM()
{
    // PORTB Pins are digital outputs
    TRISB = 0x00;
    // PORTD.RB7 is IR2110 Enable/Disable output
    TRISDbits.RD7 = 0;
    // Disable Driver before set PCPWM
    IR2110_ENABLE = 0;
    /* PTCON0 Settings
     * 1:1 Postscale, Fosc/4 (1:1 prescale), Continuous Up/Down Counting mode (bit 1-0 -> 10)
     * For Continuous Up/Down mode with interrupts for double PWM updates (bit 1-0 -> 11)
     */
    PTCON0 = 0b00000010; 
    /* PWMCON0 Settings
     * PWM 0-3 pins enabled for PWM, All PWM pairs are in complementary mode
     */
    PWMCON0 = 0b00110000;
    /* PWMCON1 Settings
     * PWM Special Event Trigger Output Postscale 1:1, 
     * A special event trigger will occur when the PWM time base is counting upwards,
     * Updates from duty cycle and period buffer registers are enabled,
     * Output overrides via the OVDCON register are asynchronous
     */
    PWMCON1 = 0b00000000;
    /* OVDCOND Settings
     * Output on PWM I/O pin is controlled by the value in the Duty Cycle register and the PWMtime base 
     */
    OVDCOND = 0b11111111;
    /* OVDCOND Settings
     * Output on PWM I/O pin is INACTIVE when the corresponding PWM output override bit is cleared 
     */
    OVDCONS = 0b00000000;
    /* FLTCONFIG Settings
     * Disable fault condition, No Fault Fault B, Inactive mode Fault B, Disable Fault B, 
     * FLTA or FLTB deactivates PWM[5:0], No Fault Fault A, Inactive mode Fault A, Disable Fault A 
     */
	FLTCONFIG = 0b00000000;
    /* PTPER [PTPERH:PTPERL] PWM Time Base Period register pairs
     * PTPER = 512, Fpwm = 9.766KHz, Center Aligned PWM, in HBridge HBpwm = 2 x Fpwm = 19.5KHz
     */
    PTPERL = 0x00;
    PTPERH = 0x02;
    /* DTCON Settings
     * Clock source for Dead Time Unit is FOSC/2, DeadTime = 2us 
     */
    DTCON = 0b00101000;
    /*PDC0 [PDC0H:PDC0L] PWM1 Generator Duty cycle register pairs
     * Resolution 11bits, 50% Duty selected
     */ 
    PDC0H = 0x03;
    PDC0L = 0xff;
    /*PDC1 [PDC1H:PDC1L] PWM1 Generator Duty cycle register pairs
     * Resolution 11bits, 50% Duty selected
     */
    PDC1H = 0x03;
    PDC1L = 0xff;
    /* PTCON1.PTEN Settings
     * PWM time base is ON
     */
    PTCON1bits.PTEN = 1;
}

/**
 * Set PWM1 pair duty cycle
 * @param _PDC0 - duty(unsigned int16) - use values from 0 to 2047
 */
void SetPWM1Duty(unsigned int _PDC0)
{
    PDC0L = _PDC0 & 0x00ff;
    PDC0H = _PDC0 >> 8;
    
}
/**
 * Set PWM2 pair duty cycle
 * @param _PDC1 - duty(unsigned int16) - use values from 0 to 2047
 */
void SetPWM2Duty(unsigned int _PDC1)
{
    PDC0L = _PDC1 & 0x00ff;
    PDC0H = _PDC1 >> 8;
}

/**
 * Enable IR2110 Outputs
 */
void IR2110Enable()
{
    IR2110_ENABLE = 1; 
}

/**
 * Disable IR2110 Outputs
 */
void IR2110Disable()
{
    IR2110_ENABLE = 0;
}
