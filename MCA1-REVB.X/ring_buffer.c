#include <xc.h>
#include "ring_buffer.h"

void Buffer_Write(unsigned char data, ringBuffer* buff)
{
    unsigned int next = (unsigned int)(buff->head + 1) % BUFFER_SIZE;
    if (next != buff->tail)
    {
        buff->buffer[buff->head] = data;
        buff->head = next;
    }
}

char Buffer_Read(ringBuffer* buff)
{
    if (buff->head == buff->tail)
        return -1;
    else
    {
        char data = buff->buffer[buff->tail];
        buff->tail = (unsigned int)(buff->tail + 1) % BUFFER_SIZE;
        return data;
    }
}

unsigned char Buffer_GetCRC8(ringBuffer* buff)
{
    unsigned char i;
    unsigned char CRC = 0;
    for (i=buff->tail; i<buff->head; i++)
    {
        CRC = CRC ^ buff->buffer[i];
    }
    return CRC;
}

