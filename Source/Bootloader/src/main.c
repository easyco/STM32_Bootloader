/*
peng xiao
test1
*/
#include "stm32f0xx_hal.h"
#include "system.h"
#include "bsp.h"
#include "uart.h"
#include "xmodem.h"
#include "bootload.h"

struct {
uint8_t  rxBuffer[XMODEM_FRAME_LENGTH];
uint16_t rxCnt;
} Receive;

int main(void)
{
    HAL_Init();
    SystemClock_Config();

	UART_Init();
	
	//UART_Transmit("STM32 Bootloader v0.0\r\n");
	Xmodem_ReceiveFile(Receive.rxBuffer, (uint16_t *)&Receive.rxCnt);

	/* 用户代码首地址放的是堆栈指针。堆栈应该指向RAM，而RAM的首地址是0x20000000；
	   读取用户代码的首地址的数据，判断是不是在RAM地址范围内，就可以知道是否存在APP代码 */
	if (((*(__IO uint32_t*)ADDR_APP_START) & 0x2FFFD000) == 0x20000000)
	{
		JumpToApp();
	}
	
	while(1)
    {
		LED_On();
	}
}
/* end of file */
