#include <xc.h>
#include "ring_buffer.h"

void BufferWrite(unsigned char data, ringBuffer* buff)
{
    unsigned int next = (unsigned int)(buff->head + 1) % BUFFER_SIZE;
    if (next != buff->tail)
    {
        buff->buffer[buff->head] = data;
        buff->head = next;
    }
}

char BufferRead(ringBuffer* buff)
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
