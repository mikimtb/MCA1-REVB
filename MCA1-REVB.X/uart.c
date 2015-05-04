#include <xc.h>

void UARTInit(long baudrate)
{
    TRISCbits.RC6 = 1;
    TRISCbits.RC7 = 1;
    
    TXSTA = 0b00100110;
    RCSTA = 0b10010000;
    
    BAUDCTLbits.BRG16 = 1;
    BAUDCTLbits.WUE = 1;
    BAUDCONbits.ABDEN = 0;
    
    SPBRG = 86;
    SPBRGH = 0;
}
void UARTSendByte(unsigned char data)
{
    while (!TXSTAbits.TRMT);
    TXREG = data;

}
