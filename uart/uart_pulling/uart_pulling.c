
#include "stm32f4xx_hal.h"
#include "string.h"
#include "board_setup.h"

#define LD3_Pin GPIO_PIN_13

static void gpio_init(void);
static void usart_init(void);

UART_HandleTypeDef uart2;

int main(void)
{
    board_setup_init();

    gpio_init();
    usart_init();
    HAL_StatusTypeDef status = HAL_OK;

    uint8_t ch; 
    char message[] = "Hello world! \r\n";
    HAL_UART_Transmit(&uart2, (uint8_t *)message, strlen(message), 10);

    while (1)
    {
        HAL_GPIO_TogglePin(GPIOD, LD3_Pin);
        uint8_t ch = 0;

        while(ch != '\n')
        {
            HAL_UART_StateTypeDef ustate = HAL_UART_GetState(&uart2);
            if (__HAL_UART_GET_FLAG(&uart2, UART_FLAG_RXNE) == SET)
            {
                status = HAL_UART_Receive(&uart2, &ch, sizeof(uint8_t), 10);
                if (status == HAL_OK)
                {
                    status = HAL_UART_Transmit(&uart2, &ch, sizeof(uint8_t), 10);
                }
                else 
                {
                    Error_Handler();
                }
            }
        };

        HAL_Delay(1);
    }
}

static void gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
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
    uart2.Instance = USART2;
    uart2.Init.BaudRate = 115200;
    uart2.Init.WordLength = UART_WORDLENGTH_8B;
    uart2.Init.StopBits = UART_STOPBITS_1;
    uart2.Init.Parity = UART_PARITY_NONE;
    uart2.Init.Mode = UART_MODE_TX_RX;
    uart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    uart2.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&uart2) != HAL_OK)
    {
        Error_Handler();
    }
}

void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(huart->Instance==USART2)
    {
        /* Peripheral clock enable */
        __HAL_RCC_USART2_CLK_ENABLE();

        __HAL_RCC_GPIOA_CLK_ENABLE();
        
        /* USART2 GPIO Configuration
        PA2     ------> USART2_TX
        PA3     ------> USART2_RX */
        GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
}