#include "main.h"
#include "can.h"
#include "tim.h"
#include "gpio.h"
#include "motor.h"
extern float angle;
extern Motor motor1;
uint32_t ptr;
extern uint8_t rxdata[8];
extern uint8_t txdata[8];
extern CAN_TxHeaderTypeDef txheader;
extern CAN_RxHeaderTypeDef rxheader;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance==htim6.Instance)
    {
        HAL_CAN_AddTxMessage(&hcan1,&txheader,txdata,&ptr);
    }
}
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    if (hcan->Instance==CAN1)
    {
        HAL_CAN_GetRxMessage(&hcan1,CAN_RX_FIFO0,&rxheader,rxdata);
        if (rxheader.StdId==0x201)
        {
          motor1.canrxmsgcallback(rxdata);
          angle=motor1.getAngle();
        }
    }
}