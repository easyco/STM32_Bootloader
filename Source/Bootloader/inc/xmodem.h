/**
******************************************************************************
* @file    xmodem.h
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
#ifndef __XMODEM_H
#define __XMODEM_H

#include <stdint.h>

//#define XMODEM_CRC16
#define XMODEM_CHECKSUM

#ifdef XMODEM_CRC16
#define XMODEM_FRAME_LENGTH     133
#else
#define XMODEM_FRAME_LENGTH     132
#endif

#define XMODEM_DATA_LENGTH      128

#define XMODEM_RX_FRAME_DELAY   ((uint32_t)0x01)
#define XMODEM_REQUEST_NUM      100

#define XMODEM_SOH		        0x01
#define XMODEM_ACK		        0x06
#define XMODEM_NAK		        0x15
#define XMODEM_EOT		        0x04

uint8_t Xmodem_ReceiveFile(uint8_t *rxBuffer, uint16_t *rxCnt);

#endif 
/* end of file */

