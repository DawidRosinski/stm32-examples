
#include "stm32f4xx_hal.h"
#include "string.h"
#include "board_setup.h"

#define LD3_Pin GPIO_PIN_13

static void gpio_init(void);
static void usart_init(void);

UART_HandleTypeDef huart2;


int main(void)
{
    board_setup_init();

    gpio_init();
    usart_init();

    while (1)
    {
        HAL_GPIO_TogglePin(GPIOD, LD3_Pin);
        char Message[] = "Write anything on Serial Terminal\r\n"; /* Message to be transmitted through UART */
        HAL_UART_Transmit(&huart2, (uint8_t *)Message, strlen(Message), 10);
        HAL_Delay(500);
    }
}

static void gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();


    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOD, LD3_Pin, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = LD3_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

static void usart_init(void)
{
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart2) != HAL_OK)
    {
        Error_Handler();
    }
}
