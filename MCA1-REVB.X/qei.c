#include <xc.h>
#include "qei.h"

/**
 * Init Quadrature Encoder Interface
 * @param _QEICON - unsigned char, QEICON register
 * @param _DFLTCON - unsigned char, DFLTCON register
 * @param _MAXCNT - unsigned int MAXCNTH:MAXCNTL register pair
 */
void InitQEI(unsigned char _QEICON, unsigned char _DFLTCON, unsigned int _MAXCNT)
{
    /*
     * All Analog Input pins except AN6 and AN7 should be set as
     * Digital I/O
     */
    ANSEL0 = ANSEL0 & 0b11000000;
    ANSEL1 = ANSEL1 & 0b00000000;
    /*
     * RA4:RA2 are digital inputs because QE signals A, B and INDX are
     * connected to these pins of microcontroller
     */
    TRISAbits.RA2 = 1;
    TRISAbits.RA3 = 1;
    TRISAbits.RA4 = 1;
    
    QEICON = _QEICON;
    DFLTCON = _DFLTCON;
    MAXCNTL = _MAXCNT;
    MAXCNTH = _MAXCNT >> 8;
    
    // Reset position counter
    POSCNTH = 0;
    POSCNTL = 0;
}

/**
 * Get quadrature encoder temporary position
 * @return unsigned int POSCNTH:POSCNTL 
 */
unsigned int GetPOSCNT()
{
    return (unsigned int)(POSCNTH << 8) & POSCNTL;
}