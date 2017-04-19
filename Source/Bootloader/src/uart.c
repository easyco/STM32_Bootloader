#include "uart.h"
#include "bsp.h"

#include <string.h>

UART_HandleTypeDef UartHandle;

void UART_Init(void)
{
	UART_CLK_Enable();

	UartHandle.Instance = UART;
	UartHandle.Init.BaudRate = 9600;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits = UART_STOPBITS_1;
	UartHandle.Init.Parity = UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode = UART_MODE_TX_RX;

	HAL_UART_Init(&UartHandle);
}

void UART_PutByte(uint8_t byte)
{
    HAL_UART_Transmit(&UartHandle, (uint8_t *)&byte, 1, 1);
}

void UART_Transmit(uint8_t *buffer)
{
	uint16_t size;
	size = strlen((const char *)buffer);
	HAL_UART_Transmit(&UartHandle, buffer, size, 1000);
}

bool UART_Receive(uint8_t *buffer, uint16_t size)
{
	if (HAL_UART_Receive(&UartHandle, buffer, size, 1000) == HAL_OK)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/* end of file */
