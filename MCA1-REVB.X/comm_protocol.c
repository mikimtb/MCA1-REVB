#include <xc.h>
#include "comm_protocol.h"

void Package_Send(comm_package* p)
{
    unsigned char i;
    p->CRC8 = Buffer_GetCRC8(&p->DATA);
    
    UARTSendByte(p->ADR);
    while(p->NUM_OF_BYTES != 0)
    {
        UARTSendByte(Buffer_Read(&p->DATA));
        p->NUM_OF_BYTES--;
    }
    UARTSendByte(p->CRC8);
}

void Package_AddData(comm_package* p, unsigned char d)
{
    Buffer_Write(d, &p->DATA);
    p->NUM_OF_BYTES++;
}
