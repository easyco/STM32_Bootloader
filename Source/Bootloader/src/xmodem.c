/**
******************************************************************************
* @file    xmodem.c
* @author  xiaopeng
* @version V2.3.0
* @date    16-Dec-2016
* @brief   xmodem传输协议
******************************************************************************
* @attention
*
*
*
******************************************************************************
*/
#include "xmodem.h"
#include "uart.h"
#include "bsp.h"

/* Xmodem传输校验方式 */
#ifndef XMODEM_CRC16
#define XMODEM_CHECKSUM
#endif

void Xmodem_LedToggle(void);
void Xmodem_PutByte(uint8_t byte);
void Xmodem_ResetRxBuffer(uint8_t *rxBuffer, uint16_t *rxCnt);
void Xmodem_WriteFileEnable(void);
void Xmodem_WriteFile(uint8_t *buffer, uint8_t size);

uint8_t Get_CheckSum(uint8_t *buffer, uint8_t length)
{
	uint8_t i = 0;
	uint8_t sum = 0;

	for (i = 0; i<length; i++)
	{
		sum = (uint8_t)(sum + *buffer++);
	}

	return sum;
}

static void Xmodem_RequestTransmit(void)
{
#ifdef XMODEM_CHECKSUM                    
	Xmodem_PutByte(0x15);
#elif defined XMODEM_CRC16
	XMODEM_PutByte('C');
#endif
	Xmodem_LedToggle();
}

static uint8_t Xmodem_RxFrame(uint8_t *rxBuffer, uint16_t *rxCnt)
{
	uint32_t n = XMODEM_RX_FRAME_DELAY;

	while (n > 0)
	{
		n--;
		#if 0
		/* 等待数据包接收完整  */
		if ((*rxCnt >= XMODEM_FRAME_LENGTH) || (rxBuffer[0] == XMODEM_EOT))
		{
			return 1;
		}
		#endif
		if (UART_Receive(rxBuffer, XMODEM_FRAME_LENGTH))
		{
			*rxCnt = XMODEM_FRAME_LENGTH;
			return 1;
		}
	}

	return 0;
}

uint8_t Xmodem_ReceiveFile(uint8_t *rxBuffer, uint16_t *rxCnt)
{
#ifdef XMODEM_CRC16
	uint16_t crc16 = 0;
#else
	uint8_t checkSum = 0;
#endif
	uint8_t n = 0;

	Xmodem_ResetRxBuffer(rxBuffer, rxCnt);

	while (Xmodem_RxFrame(rxBuffer, rxCnt) == 0)
	{
		n++;
		if (n == XMODEM_REQUEST_NUM)
		{
			return 0;
		}

		Xmodem_RequestTransmit();
	}

	Xmodem_WriteFileEnable();

	while (rxBuffer[0] != XMODEM_EOT)
	{
#ifdef XMODEM_CRC16
		CRC16 = get_crc16(&rxBuffer[3], XMODEM_DATA_LENGTH);
		if (((uint8_t)(CRC16 >> 8) == rxBuffer[XMODEM_FRAME_LENGTH - 2]) && 
		((uint8_t)CRC16 == rxBuffer[XMODEM_FRAME_LENGTH - 1]))
#elif defined (XMODEM_CHECKSUM)
		checkSum = Get_CheckSum((uint8_t *)&rxBuffer[3], XMODEM_DATA_LENGTH);
		if (checkSum == rxBuffer[XMODEM_FRAME_LENGTH - 1])
#endif
		{
			Xmodem_WriteFile((uint8_t *)&rxBuffer[3], XMODEM_DATA_LENGTH);
			Xmodem_PutByte(XMODEM_ACK);
		}
		else
		{
			Xmodem_PutByte(XMODEM_NAK);
		}
		
		Xmodem_ResetRxBuffer(rxBuffer, rxCnt);
		Xmodem_RxFrame(rxBuffer, rxCnt);
	}

	/* 收到XMODEM_EOT */
	Xmodem_PutByte(XMODEM_ACK);
	return 1;
}
