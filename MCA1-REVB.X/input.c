#include <xc.h>
#include "input.h"

/**
 * Digital inputs initialization
 */
void InputInit()
{
    // Define PORTD5 and PORTD6 as digital inputs
    TRISDbits.RD5 = 1;
    TRISDbits.RD6 = 1;
}

/**
 * Read Digital Input C1
 * @return - TRUE if input is held to low, FALSE if input is held to high 
 */
bit InputC1()
{
    return PORTDbits.RD5;
}

/**
 * Read Digital Input C2
 * @return - TRUE if input is held to low, FALSE if input is held to high 
 */
bit InputC2()
{
    return PORTDbits.RD6;
}

