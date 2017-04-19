#include "bootload.h"
#include "bsp.h"
#include "uart.h"
#include "xmodem.h"

uint8_t FlashBuffer[FLASH_PAGE_SIZE];

typedef void (*pFunction)(void);
void JumpToApp(void)
{
	__disable_irq();
	uint32_t jumpAddr = *(__IO uint32_t*) (ADDR_APP_START + 4);
	pFunction jumpToAddr = (pFunction)jumpAddr;
	/* Init application stack pointer */
	__set_MSP(*(__IO uint32_t*) ADDR_APP_START);
	jumpToAddr();
}

void Xmodem_LedToggle(void)
{
	LED_Toggle();
}

void Xmodem_PutByte(uint8_t byte)
{
	UART_PutByte(byte);
}

void Xmodem_ResetRxBuffer(uint8_t *rxBuffer, uint16_t *rxCnt)
{
	rxBuffer[0] = 0;
	*rxCnt = 0;
}

void Xmodem_WriteFileEnable(void)
{
	HAL_FLASH_Unlock();
}

void Xmodem_WriteFile(uint8_t *frameData, uint8_t frameSize)
{
	static FLASH_EraseInitTypeDef EraseInitStruct;
	static uint32_t flashAddr = ADDR_APP_START;
	static uint16_t buffAddr;
	uint32_t data;
	uint16_t i = 0;
	uint32_t PageError = 0;

	for (i=0; i<XMODEM_DATA_LENGTH; i++)
	{
		FlashBuffer[buffAddr] = frameData[i];
		buffAddr ++;
	}

	if (buffAddr  == FLASH_PAGE_SIZE)
	{
		buffAddr = 0;

		HAL_FLASH_Unlock();

		EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
		EraseInitStruct.PageAddress = flashAddr;
		EraseInitStruct.NbPages = 1;
		HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);

		i = 0;
		while(i<FLASH_PAGE_SIZE)
		{
			data = ((uint32_t)FlashBuffer[i]) | ((uint32_t)FlashBuffer[i+1]<<8) |
					((uint32_t)FlashBuffer[i+2]<<16) | ((uint32_t)FlashBuffer[i+3]<<24);
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, flashAddr, data);
			i += 4;
			flashAddr += 4;
		}

		HAL_FLASH_Lock();
	}
}
