#include <xc.h>
#include "interrupts.h"

//char t_interruptsID;


void InterruptEnable(enum t_interruptsID intID)
{
    
    switch (intID)
    {
        case GIEH_b:
            INTCONbits.GIEH = 1;
            break;
        case GIEL_b:
            INTCONbits.GIEL = 1;
            break;
        case RCIE_b:
            PIE1bits.RCIE = 1;
            break;
    }
}
