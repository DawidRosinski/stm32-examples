
#include "stm32f4xx_hal.h"
#include "board_setup.h"

// STM32_STATUS_LED
// GPIOPin(GPIOC, GPIO_PIN_15, GPIOPin::Type::Output), // STM32_STATUS_LED

#define LED_RED_PORT GPIOF
#define LED_BLUE_PORT GPIOF
#define LED_GREEN_PORT GPIOE

#define LED_RED_PIN GPIO_PIN_14
#define LED_BLUE_PIN GPIO_PIN_15
#define LED_GREEN_PIN GPIO_PIN_7


static void gpio_init(void);

int main(void)
{
    board_setup_init();

    gpio_init();

    while (1)
    {
        HAL_GPIO_TogglePin(LED_GREEN_PORT, LED_GREEN_PIN);
        HAL_Delay(500);
    }
}

static void gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();

    /* Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(LED_RED_PORT, LED_RED_PIN, GPIO_PIN_SET);

    GPIO_InitStruct.Pin = LED_RED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(LED_RED_PORT, &GPIO_InitStruct);

    /* Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(LED_BLUE_PORT, LED_BLUE_PIN, GPIO_PIN_SET);
    GPIO_InitStruct.Pin = LED_BLUE_PIN;
    HAL_GPIO_Init(LED_RED_PORT, &GPIO_InitStruct);

    HAL_GPIO_WritePin(LED_GREEN_PORT, LED_GREEN_PIN, GPIO_PIN_SET);
    GPIO_InitStruct.Pin = LED_GREEN_PIN;
    HAL_GPIO_Init(LED_GREEN_PORT, &GPIO_InitStruct);
}
