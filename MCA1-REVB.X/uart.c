#include <xc.h>
#include "uart.h"

void UARTInit(unsigned long baudrate)
{
    unsigned int divisor;
    
    TRISCbits.RC6 = 1;
    TRISCbits.RC7 = 1;
    
    //RS-485 nRE/DE Enable
    TRISDbits.RD4 = 0;                                                          // RS-485 RE/DE are connected to RD4, so RD4 is configurated as an output pin 
    PORTDbits.RD4 = 0;                                                          // Enable RS-485 receiver
    
    TXSTA = 0b00100110;
    RCSTA = 0b10010000;
    
    BAUDCTLbits.BRG16 = 1;
    BAUDCTLbits.WUE = 0;
    BAUDCONbits.ABDEN = 0;
    
    switch (baudrate)
    {
        case 9600:
            divisor = 1040;
            break;
        case 19200:
            divisor = 520;
            break;
        case 57600:
            divisor = 172;
            break;
        case 115200:
            divisor = 86;
            break;
        case 921600:
            divisor = 10;
            break;
    }
    
    SPBRG = divisor;
    SPBRGH = divisor >> 8;
    
    IPR1bits.RCIP = 0;                                                          // UART RX Interrupt is low priority
    PIE1bits.RCIE = 1;                                                          // Enable UART RX Interrupt
}

void UartSendByte(unsigned char data)
{
    while (!TXSTAbits.TRMT);
    PORTDbits.RD4 = 1;
    TXREG = data;
    while (!TXSTAbits.TRMT);
    PORTDbits.RD4 = 0;
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
