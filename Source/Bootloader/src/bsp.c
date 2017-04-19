#include "bsp.h"

static void BSP_InitLED(void)
{
    GPIO_InitTypeDef  gpioInit;

	LED_K1_GPIO_CLK_Enable();
	LED_A1_GPIO_CLK_Enable();
	
	gpioInit.Mode = GPIO_MODE_OUTPUT_PP;
	gpioInit.Pull = GPIO_PULLDOWN;
	gpioInit.Speed = GPIO_SPEED_FREQ_MEDIUM;

	gpioInit.Pin = LED_K1_GPIO_PIN;
	HAL_GPIO_Init(LED_K1_GPIO_PORT, &gpioInit);
	
	gpioInit.Pin = LED_A1_GPIO_PIN;
	HAL_GPIO_Init(LED_A1_GPIO_PORT, &gpioInit);

    HAL_GPIO_WritePin(LED_K1_GPIO_PORT, LED_K1_GPIO_PIN, GPIO_PIN_RESET);
}

static void BSP_InitUART(void)
{
    GPIO_InitTypeDef  gpioInit;

	UART_TX_GPIO_CLK_Enable();
	UART_RX_GPIO_CLK_Enable();
	
	gpioInit.Mode = GPIO_MODE_AF_PP;
	gpioInit.Pull = GPIO_PULLUP;
	gpioInit.Speed = GPIO_SPEED_FREQ_HIGH;
	
	gpioInit.Pin = UART_TX_PIN;
	gpioInit.Alternate = UART_TX_AF;
	HAL_GPIO_Init(UART_TX_GPIO_PORT, &gpioInit);

	gpioInit.Pin = UART_RX_PIN;
	gpioInit.Alternate = UART_RX_AF;
	HAL_GPIO_Init(UART_RX_GPIO_PORT, &gpioInit);
}

void HAL_MspInit(void)
{
    BSP_InitLED();
    BSP_InitUART();
}

