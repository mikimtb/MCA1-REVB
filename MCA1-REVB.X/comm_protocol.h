#include <xc.h>
#include "ring_buffer.h"
#include "uart.h"

typedef struct package
{
    unsigned char ADR;
    unsigned char NUM_OF_BYTES;
    ringBuffer DATA;
    unsigned char CRC8;
} comm_package;

void Package_Send(comm_package*);
void Package_AddData(comm_package*, unsigned char);
 