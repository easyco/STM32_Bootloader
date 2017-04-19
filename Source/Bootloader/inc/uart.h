#ifndef __UART_H
#define __UART_H

#include "stm32f0xx_hal.h"
#include <stdbool.h>

void UART_Init(void);
void UART_PutByte(uint8_t byte);
void UART_Transmit(uint8_t *buffer);
bool UART_Receive(uint8_t *buffer, uint16_t size);

#endif 
/* end of file */
