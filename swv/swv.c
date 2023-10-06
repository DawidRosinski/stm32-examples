#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "board_setup.h"

#define LD5_Pin GPIO_PIN_14
#define LD5_GPIO_Port GPIOD

static void gpio_init(void);

int _write(int file, char *ptr, int len)
{   
    int DataIdx;

    for(DataIdx = 0; DataIdx < len; DataIdx++)
    {
        ITM_SendChar(*ptr++);
    }
    
    return len;
}

int main(void)
{
    board_setup_init();
    gpio_init();

    while (1)
	{
        HAL_GPIO_TogglePin(GPIOD, LD5_Pin);
        printf("Hello word!\n");
        HAL_Delay(200);
        HAL_GPIO_TogglePin(GPIOD, LD5_Pin);
        HAL_Delay(200);
    }
}

void gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOD_CLK_ENABLE();


    /* Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOD, LD5_Pin, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = LD5_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}
