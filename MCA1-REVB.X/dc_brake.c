#include <xc.h>
#include "dc_brake.h"

/**
 * Initialize CCP1 as PWM
 * fc = 19.5KHz
 */
void DCBrake_PWMInit()
{
    TRISCbits.RC2 = 1;                                                          // Turn OFF PWM by making RC2 as input pin
    PR2 = 127;                                                                  // Set PWM period register
    CCP1CON = 0b00001100;                                                       // Setup for PWM mode 5:4 are PWM Duty Cycle LSB 
    CCPR1L = 0x00;                                                              // Eight high bits of duty cycle 
    T2CON = 0b00000101;                                                         // Timer2 On, 1:1 Post, 4x prescale
    //TRISCbits.RC2 = 0;                                                          // Turn ON PWM by making RC2 as output pin 
}

/**
 * Set PWM Duty cycle
 * @param duty(unsigned int16) - use values from 0 to 511
 */
void SetDCBrake_PWMDuty(unsigned int duty)
{
    CCP1CONbits.DC1B0 = duty & 1;                                               //set low bit 
    CCP1CONbits.DC1B1 = (duty >> 1) & 1;                                        //set second lowest 
    CCPR1L = (duty >> 2);                                                       //set highest eight
}

/**
 * Release DC Break
 */
void DCBrake_Release()
{
    TRISCbits.RC2 = 0;
}

/**
 * Catch DC Break
 */
void DCBrake_Catch()
{
    TRISCbits.RC2 = 1;
}

/**
 * Select DC Brake Nominal Voltage
 * @param DCBrakeNominalVoltage(unsigned int8) - DC Brake Nominal Voltage [V], 
 * must be lower than Driver HV(High Voltage) Supply Input Voltage [V]
 * @param HVSupplyVoltage(unsigned int8) - Driver HV(High Voltage) Supply Input [V]
 */
int SetDCBrake_NominalVoltage(unsigned short DCBrakeNominalVoltage, unsigned short HVSupplyVoltage)
{
    if (DCBrakeNominalVoltage >= HVSupplyVoltage)                               // If DC Brake Nominal Voltage is greater than HVSupplyVoltage
        return 1;                                                               // Return 1 to trigger Under Voltage error
    
    float sPWMQuantum = HVSupplyVoltage / 512.0;
    SetDCBrake_PWMDuty(DCBrakeNominalVoltage / sPWMQuantum);
    
    return 0;
}