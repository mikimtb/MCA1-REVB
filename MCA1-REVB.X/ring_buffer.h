#include <xc.h>
#define BUFFER_SIZE 32

typedef struct circular_buffer
{
    unsigned char buffer[BUFFER_SIZE];
    volatile unsigned int head;
    volatile unsigned int tail;
} ringBuffer;



void Buffer_Write(unsigned char, ringBuffer*);
char Buffer_Read(ringBuffer*);
unsigned char Buffer_GetCRC8(ringBuffer*);

