#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "board_setup.h"

#define LD5_Pin GPIO_PIN_14
#define LD5_GPIO_Port GPIOD

static void gpio_init(void);

extern void initialise_monitor_handles(void);

int main(void)
{
    // reqired for semihosting
    initialise_monitor_handles();

    board_setup_init();
    gpio_init();

    printf("Welcome from semihosting\n");

    while (1)
    {
        HAL_GPIO_TogglePin(GPIOD, LD5_Pin);
        HAL_Delay(100);
        printf("Hello world\n");
    }
}

void gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOD_CLK_ENABLE();


    /* Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOD, LD5_Pin, GPIO_PIN_RESET);

    /* Configure GPIO pins : LD4_Pin LD3_Pin LD5_Pin LD6_Pin
                            Audio_RST_Pin */
    GPIO_InitStruct.Pin = LD5_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}
