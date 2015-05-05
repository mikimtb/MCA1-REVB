#include <xc.h>
#include "uart.h"

void UARTInit(long baudrate)
{
    TRISCbits.RC6 = 1;
    TRISCbits.RC7 = 1;
    
    //RS-485 Enable
    TRISDbits.RD4 = 0;                                                          // RS-485 RE/DE are connected to RD4, so RD4 is configurated as an output pin 
    PORTDbits.RD4 = 0;                                                          // Enable RS-485 receiver
    
    TXSTA = 0b00100110;
    RCSTA = 0b10010000;
    
    BAUDCTLbits.BRG16 = 1;
    BAUDCTLbits.WUE = 1;
    BAUDCONbits.ABDEN = 0;
    
    SPBRG = 10;
    SPBRGH = 0;
}
void UARTSendBytes(unsigned char *data, int dataLength)
{
    int i;
    for (i = 0; i < dataLength; i++) 
    {
        while (!TXSTAbits.TRMT);
        PORTDbits.RD4 = 1;
        TXREG = data[i];
    }
    while (!TXSTAbits.TRMT);
    PORTDbits.RD4 = 0;

}
