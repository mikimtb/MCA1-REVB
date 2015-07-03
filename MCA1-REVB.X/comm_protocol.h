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

typedef enum 
{
    ADDRESING,
    DATA_LENGTH_RECEIVING,
    DATA_RECEIVING,
    CRC8_RECEIVING
} state_t;

comm_package in = {120, 0, {{0}, 0, 0}, 0};
comm_package out = {130, 0, {{0}, 0, 0}, 0};
state_t RCV_STATE = ADDRESING;
unsigned char RCV_LENGTH = 0;

void Package_Send(comm_package*);
void Package_WriteDataByte(comm_package*, unsigned char);
unsigned char Package_ReadDataByte(comm_package*); 
unsigned char Package_GetLength(comm_package*);
void Package_SetADR(comm_package*, unsigned char);
unsigned char Package_GetADR(comm_package*);
unsigned char Package_GetCRC8(comm_package*);
unsigned char Package_CalculateCRC8(comm_package*);