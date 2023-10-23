
#include "stm32f4xx_hal.h"
#include "string.h"
#include "board_setup.h"


#define CAN_PREEMPTION_PRIORITY				14u
#define CAN_PREEMPTION_SUBPRIORITY			0u

#if (_STM32_BOARD == _STM32_F4_DISC)
    #define LED_PORT GPIOD
    #define LED_PIN GPIO_PIN_13
#elif (_STM32_BOARD == _STM32_CUSTOM)
    #define LED_PORT GPIOE
    #define LED_PIN GPIO_PIN_7
    #define LED_RED_PORT GPIOF
    #define LED_BLUE_PORT GPIOF
    #define LED_GREEN_PORT GPIOE

    #define LED_RED_PIN GPIO_PIN_14
    #define LED_BLUE_PIN GPIO_PIN_15
    #define LED_GREEN_PIN GPIO_PIN_7
#endif


#if (_STM32_BOARD == _STM32_F4_DISC)
    #define LED_PORT_CLK_EN() __HAL_RCC_GPIOD_CLK_ENABLE()
#elif (_STM32_BOARD == _STM32_CUSTOM)
    #define LED_PORT_CLK_EN() __HAL_RCC_GPIOE_CLK_ENABLE()
#endif


typedef enum
{
	CAN_ATTR_STD_E = 0,
	CAN_ATTR_EXT_E
} can_attr_t;

typedef struct
{
	uint32_t id;
	uint16_t dlc;
	uint8_t data[8];
	can_attr_t attr;
} can_msg_t;


static void gpio_init(void);
static void can_init(void);
static uint16_t can_tx(can_msg_t *msg);
static uint16_t can_rx(can_msg_t *msg);

static CAN_HandleTypeDef can1;

int main(void)
{
    HAL_StatusTypeDef status = HAL_OK;
    can_msg_t msg = {0};

    board_setup_init();
    gpio_init();
    can_init();

    while (1)
    {
        HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
        msg.data[0]++;
        status = can_rx(&msg);
        if(status == HAL_OK)
        {
            can_tx(&msg);
        }
        // HAL_Delay(500);
    }
}

static void gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    LED_PORT_CLK_EN();
    __HAL_RCC_GPIOF_CLK_ENABLE();


    /* Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

#if (_STM32_BOARD == _STM32_CUSTOM)
    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(LED_RED_PORT, LED_RED_PIN, GPIO_PIN_SET);

    GPIO_InitStruct.Pin = LED_RED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(LED_RED_PORT, &GPIO_InitStruct);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(LED_BLUE_PORT, LED_BLUE_PIN, GPIO_PIN_SET);
    GPIO_InitStruct.Pin = LED_BLUE_PIN;
    HAL_GPIO_Init(LED_RED_PORT, &GPIO_InitStruct);

    HAL_GPIO_WritePin(LED_GREEN_PORT, LED_GREEN_PIN, GPIO_PIN_SET);
    GPIO_InitStruct.Pin = LED_GREEN_PIN;
    HAL_GPIO_Init(LED_GREEN_PORT, &GPIO_InitStruct);
#endif
}

static void can_init(void)
{
    can1.Instance = CAN1;
    can1.Init.Prescaler = 8;
    can1.Init.Mode = CAN_MODE_NORMAL;
    can1.Init.SyncJumpWidth = CAN_SJW_1TQ;
    can1.Init.TimeSeg1 = CAN_BS1_16TQ;
    can1.Init.TimeSeg2 = CAN_BS2_4TQ;
    can1.Init.TimeTriggeredMode = DISABLE;
    can1.Init.AutoBusOff = DISABLE;
    can1.Init.AutoWakeUp = DISABLE;
    can1.Init.AutoRetransmission = DISABLE;
    can1.Init.ReceiveFifoLocked = DISABLE;
    can1.Init.TransmitFifoPriority = DISABLE;
    if (HAL_CAN_Init(&can1) != HAL_OK)
    {
        Error_Handler();
    }

    uint32_t u32MsgId = (uint32_t)0x11111100;
    uint32_t acceptanceMask = 0x03FFFF00u;

    CAN_FilterTypeDef sFilterConfig = { 0 };
    sFilterConfig.FilterActivation = ENABLE;
    sFilterConfig.FilterBank = 0;
    sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    sFilterConfig.FilterIdHigh = (uint32_t)((u32MsgId >> 13u) & 0xFFFFu);
    sFilterConfig.FilterIdLow = (uint32_t)(((u32MsgId << 3u) & 0xFFF8u) | 4u);
    sFilterConfig.FilterMaskIdHigh = (uint32_t)((acceptanceMask >> 13u) & 0xFFFFu);
    sFilterConfig.FilterMaskIdLow = (uint32_t)(((acceptanceMask << 3u) & 0xFFF8u) | 4u);
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    // sFilterConfig.SlaveStartFilterBank = 0; // doesn't care for single CAN

    u32MsgId = (uint32_t)0x12222200;
    acceptanceMask = 0xFFFFFF00u;

    CAN_FilterTypeDef sFilterConfig2 = { 0 };
    sFilterConfig2.FilterActivation = ENABLE;
    sFilterConfig2.FilterBank = 1;
    sFilterConfig2.FilterFIFOAssignment = CAN_RX_FIFO0;
    sFilterConfig2.FilterIdHigh = (uint32_t)((u32MsgId >> 13u) & 0xFFFFu);
    sFilterConfig2.FilterIdLow = (uint32_t)(((u32MsgId << 3u) & 0xFFF8u) | 4u);
    sFilterConfig2.FilterMaskIdHigh = (uint32_t)((acceptanceMask >> 13u) & 0xFFFFu);
    sFilterConfig2.FilterMaskIdLow = (uint32_t)(((acceptanceMask << 3u) & 0xFFF8u) | 4u);
    sFilterConfig2.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig2.FilterScale = CAN_FILTERSCALE_32BIT;

    HAL_StatusTypeDef stat = HAL_CAN_ConfigFilter(&can1, &sFilterConfig);
    stat = HAL_CAN_ConfigFilter(&can1, &sFilterConfig2);

    HAL_CAN_Start(&can1);
}

static uint16_t can_rx(can_msg_t *msg)
{
    HAL_StatusTypeDef status = HAL_TIMEOUT;
    CAN_RxHeaderTypeDef header;

    uint32_t msg_num = HAL_CAN_GetRxFifoFillLevel(&can1, CAN_RX_FIFO0);

    if (msg_num > 0)
    {
        status = HAL_CAN_GetRxMessage(&can1, CAN_RX_FIFO0, &header, msg->data);
        msg->id = header.ExtId;
        msg->attr = CAN_ATTR_EXT_E;
        msg->dlc = header.DLC;
        return status;
    }

    msg_num = HAL_CAN_GetRxFifoFillLevel(&can1, CAN_RX_FIFO1);

    if (msg_num > 0)
    {
        status = HAL_CAN_GetRxMessage(&can1, CAN_RX_FIFO1, &header, msg->data);
        msg->id = header.ExtId;
        msg->attr = CAN_ATTR_EXT_E;
        msg->dlc = header.DLC;
        return status;
    }
    

    return status;
}

static uint16_t can_tx(can_msg_t *msg)
{
    CAN_TxHeaderTypeDef sTxHeader;
    HAL_StatusTypeDef status = HAL_OK;
    uint16_t u16ReturnValue = 0;
    uint8_t aData[8];
    uint32_t TxMailbox;

    if(msg == NULL)
    {
        // return error code
        return -1;
    }

    if(msg->dlc == CAN_ATTR_STD_E)
    {
        sTxHeader.StdId = msg->id;
        sTxHeader.IDE = CAN_ID_STD;
    }
    else
    {
        sTxHeader.ExtId = msg->id;
        sTxHeader.IDE = CAN_ID_EXT;
    }

    sTxHeader.RTR = CAN_RTR_DATA;
    sTxHeader.DLC = msg->dlc;
    memcpy(aData, msg->data, sizeof(msg->data));
    status = HAL_CAN_AddTxMessage(&can1, &sTxHeader, aData,  &TxMailbox);
    return status;
}

void HAL_CAN_MspInit(CAN_HandleTypeDef* hcan)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(hcan->Instance==CAN1)
  {
    /* Peripheral clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

#if (_STM32_BOARD == _STM32_F4_DISC)
    __HAL_RCC_GPIOD_CLK_ENABLE();       // F4 discovery
#elif (_STM32_BOARD == _STM32_CUSTOM)
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOI_CLK_ENABLE();
#endif

#if (_STM32_BOARD == _STM32_F4_DISC)
    /**CAN1 GPIO Configuration
    PD0     ------> CAN1_RX
    PD1     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
#elif (_STM32_BOARD == _STM32_CUSTOM)
    /**CAN1 GPIO Configuration
    PI9     ------> CAN1_RX
    PH13     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_13;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
#endif
  }

}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* hcan)
{
  if(hcan->Instance==CAN1)
  {
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

#if (_STM32_BOARD == _STM32_F4_DISC)
    /**CAN1 GPIO Configuration
    PD0     ------> CAN1_RX
    PD1     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_0|GPIO_PIN_1);
#elif (_STM32_BOARD == _STM32_CUSTOM)
    /**CAN1 GPIO Configuration
    PI9     ------> CAN1_RX
    PH13     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOI, GPIO_PIN_9);
    HAL_GPIO_DeInit(GPIOH, GPIO_PIN_13);
#endif
  }

}