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

void Package_WriteDataByte(comm_package* p, unsigned char d)
{
    Buffer_Write(d, &p->DATA);
    p->NUM_OF_BYTES++;
}

unsigned char Package_ReadDataByte(comm_package* p)
{
    p->NUM_OF_BYTES--;
    return Buffer_Read(&p->DATA);
}

unsigned char Package_GetLength(comm_package* p)
{
    return p->NUM_OF_BYTES;
}

void Package_SetADR(comm_package* p, unsigned char adr)
{
    p->ADR = adr;
}

unsigned char Package_GetADR(comm_package* p)
{
    return p->ADR;
}

unsigned char Package_GetCRC8(comm_package* p)
{
    return p->CRC8;
}

unsigned char Package_CalculateCRC8(comm_package* p)
{
    p->CRC8 = Buffer_GetCRC8(&p->DATA);
    return p->CRC8;
}
