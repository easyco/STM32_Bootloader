#ifndef __BOOTLOAD_H
#define __BOOTLOAD_H

#include "stm32f0xx_hal.h"

#define RAM_SIZE            (0x2000)
#define FLASH_SIZE          (32)	// 32 Pages
#define BOOT_SIZE           (6) 	// 6 Pages
#define ADDR_APP_START  	((uint32_t)0x08000000 + BOOT_SIZE * FLASH_PAGE_SIZE)	// App start address
#define APP_PAGE_NUM        (FLASH_SIZE - BOOT_SIZE)

void JumpToApp(void);

#endif 
/* end of file */
