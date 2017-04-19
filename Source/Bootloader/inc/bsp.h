#ifndef __BSP_H
#define __BSP_H

#include "stm32f0xx_hal.h"

#define LED_K1_GPIO_PORT			GPIOA
#define LED_K1_GPIO_PIN				GPIO_PIN_15
#define LED_K1_GPIO_CLK_Enable()	__GPIOA_CLK_ENABLE()
#define LED_K1_GPIO_CLK_Disable()	__GPIOA_CLK_DISABLE()

#define LED_A1_GPIO_PORT			GPIOA
#define LED_A1_GPIO_PIN				GPIO_PIN_8
#define LED_A1_GPIO_CLK_Enable()	__GPIOA_CLK_ENABLE()
#define LED_A1_GPIO_CLK_Disable()	__GPIOA_CLK_DISABLE()

#define LED_On()                    HAL_GPIO_WritePin(LED_A1_GPIO_PORT, LED_A1_GPIO_PIN, GPIO_PIN_SET)
#define LED_Off()                   HAL_GPIO_WritePin(LED_A1_GPIO_PORT, LED_A1_GPIO_PIN, GPIO_PIN_RESET)
#define LED_Toggle()                HAL_GPIO_TogglePin(LED_A1_GPIO_PORT, LED_A1_GPIO_PIN)

#define UART                        USART1
#define UART_CLK_Enable()           __HAL_RCC_USART1_CLK_ENABLE()
#define UART_RX_GPIO_CLK_Enable()   __HAL_RCC_GPIOA_CLK_ENABLE()
#define UART_TX_GPIO_CLK_Enable()   __HAL_RCC_GPIOA_CLK_ENABLE()

#define UART_FORCE_Reset()          __HAL_RCC_USART1_FORCE_RESET()
#define UART_RELEASE_Reset()        __HAL_RCC_USART1_RELEASE_RESET()

#define UART_TX_PIN                 GPIO_PIN_9
#define UART_TX_GPIO_PORT           GPIOA
#define UART_TX_AF                  GPIO_AF1_USART1
#define UART_RX_PIN                 GPIO_PIN_10
#define UART_RX_GPIO_PORT           GPIOA
#define UART_RX_AF                  GPIO_AF1_USART1

#endif
/* end of file */
