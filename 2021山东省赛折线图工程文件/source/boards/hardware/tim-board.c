/**********************************************************************************************************
*ʹ��˵����
*TIM2��TIM3�ӿں������û�Ҫʹ��TIM2��3�Ķ�ʱ���ж�ʱ���ȵ���Tim2McuInit()��Tim3McuInit(),�������������������
*�����ڣ���λ��MS��ȡֵ1~1023MS���û����ж�Ӧ�ó�������ӵ����ļ�ĩβ��HAL_TIM_PeriodElapsedCallback()�ĺ�����
*�״�����ʱ�����к�ÿ���ж�����ʱ�䵽�������ж��ڵ�Ӧ�ó��򣬲��Ұ��ж������ظ���
*
*
**********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "tim-board.h"

/** @addtogroup STM32L1xx_HAL_Examples
  * @{
  */

/** @addtogroup TIM_TimeBase
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* variables -----------------------------------------------------------------*/

/* TIM handle declaration */
TIM_HandleTypeDef    Tim2Handle;
TIM_HandleTypeDef    Tim3Handle;
TimerCallback timer2Callback = NULL;
TimerCallback timer3Callback = NULL;

/* Private functions ---------------------------------------------------------*/

/**********************************************************************************************
*������void Tim2McuInit(uint16_t PeriodValueMs)
*���ܣ�TIM2��ʱ����ʼ���������ж�����PeriodValueMs����
*���룺uint16_t PeriodValueMs�ж����ڣ���λ:ms��ȡֵ1~1023
*�������
����˵������ʱ����16λ��ʱ�������ʱ������1024ms.ԭ��64000��Ƶ����ʱ1ms������Ϊ64-1�����Զ�ʱ
*					16λ���ֵΪ65535���������65536=64*X�����X=1024
**********************************************************************************************/
void Tim2McuInit(uint16_t PeriodValueMs)
{
    uint32_t uwPrescalerValue = 0;
    /*##-1- Configure the TIM peripheral #######################################*/
    /* -----------------------------------------------------------------------
      In this example TIM2 input clock (TIM2CLK)  is set to APB1 clock (PCLK1),
      since APB1 prescaler is equal to 1.
        TIM2CLK = PCLK1
        PCLK1 = HCLK
        => TIM2CLK = HCLK = SystemCoreClock
      To get TIM2 counter clock at 10 KHz, the Prescaler is computed as following:
      Prescaler = (TIM2CLK / TIM2 counter clock) - 1
      Prescaler = (SystemCoreClock /64 KHz) - 1

      Note:
       SystemCoreClock variable holds HCLK frequency and is defined in system_stm32l1xx.c file.
       Each time the core clock (HCLK) changes, user had to update SystemCoreClock
       variable value. Otherwise, any configuration based on this variable will be incorrect.
       This variable is updated in three ways:
        1) by calling CMSIS function SystemCoreClockUpdate()
        2) by calling HAL API function HAL_RCC_GetSysClockFreq()
        3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency
    ----------------------------------------------------------------------- */

    /* Compute the prescaler value to have TIM2 counter clock equal to 64KHz */
    uwPrescalerValue = (uint32_t)(SystemCoreClock / 64000) - 1;

    /* Set TIM2 instance */
    Tim2Handle.Instance = TIM2;

    /* Initialize TIM2 peripheral as follows:
         + Period = 1000 - 1
         + Prescaler = (SystemCoreClock/64000) - 1
         + ClockDivision = 0
         + Counter direction = Up
    */
    Tim2Handle.Init.Period            = PeriodValueMs*64 - 1;//����PeriodValueMs����
    Tim2Handle.Init.Prescaler         = uwPrescalerValue;
    Tim2Handle.Init.ClockDivision     = 0;
    Tim2Handle.Init.CounterMode       = TIM_COUNTERMODE_UP;

    if (HAL_TIM_Base_Init(&Tim2Handle) != HAL_OK)
    {
        /* Initialization Error */
        printf("��ʱ��2��ʼ��ʧ�ܣ�\r\n");
    }

    /*##-2- Start the TIM Base generation in interrupt mode ####################*/
    /* Start Channel1 */
    if (HAL_TIM_Base_Start_IT(&Tim2Handle) != HAL_OK)
    {
        /* Starting Error */
        printf("��ʱ��2�����ж�ʧ�ܣ�\r\n");
    }
}

/**********************************************************************************************
*������void Tim3McuInit(uint16_t PeriodValueMs)
*���ܣ�TIM3��ʱ����ʼ���������ж�����PeriodValueMs����
*���룺uint16_t PeriodValueMs�ж����ڣ���λ:0.25ms��ȡֵ1~1023
*�������
*����˵������ʱ����16λ��ʱ�������ʱ������1024ms.ԭ��16000��Ƶ����ʱ0.25ms������Ϊ64-1�����Զ�ʱ
*					16λ���ֵΪ65535���������65536=64*X�����X=1024
**********************************************************************************************/
void Tim3McuInit(uint16_t PeriodValueMs)
{
    uint32_t uwPrescalerValue = 0;
    /*##-1- Configure the TIM peripheral #######################################*/
    /* -----------------------------------------------------------------------
      In this example TIM3 input clock (TIM3CLK)  is set to APB1 clock (PCLK1),
      since APB1 prescaler is equal to 1.
        TIM3CLK = PCLK1
        PCLK1 = HCLK
        => TIM3CLK = HCLK = SystemCoreClock
      To get TIM3 counter clock at 64 KHz, the Prescaler is computed as following:
      Prescaler = (TIM3CLK / TIM3 counter clock) - 1
      Prescaler = (SystemCoreClock /64 KHz) - 1

      Note:
       SystemCoreClock variable holds HCLK frequency and is defined in system_stm32l1xx.c file.
       Each time the core clock (HCLK) changes, user had to update SystemCoreClock
       variable value. Otherwise, any configuration based on this variable will be incorrect.
       This variable is updated in three ways:
        1) by calling CMSIS function SystemCoreClockUpdate()
        2) by calling HAL API function HAL_RCC_GetSysClockFreq()
        3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency
    ----------------------------------------------------------------------- */

    /* Compute the prescaler value to have TIM3 counter clock equal to 64000 Hz */
    uwPrescalerValue = (uint32_t)(SystemCoreClock / 64000) - 1;

    /* Set TIM3 instance */
    Tim3Handle.Instance = TIM3;

    /* Initialize TIM3 peripheral as follows:
         + Period = 1000 - 1
         + Prescaler = (SystemCoreClock/64000) - 1
         + ClockDivision = 0
         + Counter direction = Up
    */
    //Tim3Handle.Init.Period            = (PeriodValueMs*64) - 1;//����PeriodValueMs����
    Tim3Handle.Init.Period            = (PeriodValueMs*16) - 1;//����PeriodValueMs����
    Tim3Handle.Init.Prescaler         = uwPrescalerValue;
    Tim3Handle.Init.ClockDivision     = 0;
    Tim3Handle.Init.CounterMode       = TIM_COUNTERMODE_UP;

    if (HAL_TIM_Base_Init(&Tim3Handle) != HAL_OK)
    {
        /* Initialization Error */
        printf("��ʱ��3��ʼ��ʧ�ܣ�\r\n");
    }

    /*##-2- Start the TIM Base generation in interrupt mode ####################*/
    /* Start Channel1 */
    if (HAL_TIM_Base_Start_IT(&Tim3Handle) != HAL_OK)
    {
        /* Starting Error */
        printf("��ʱ��3�����ж�ʧ�ܣ�\r\n");
    }
}

/**
  * @brief TIM MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  * @param htim: TIM handle pointer
  * @retval None
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM2)
    {
        /*##-1- Enable peripherals and GPIO Clocks #################################*/
        /* TIMx Peripheral clock enable */
        TIM2_CLK_ENABLE();

        /*##-2- Configure the NVIC for TIMx ########################################*/
        /* Set the TIMx priority */
        HAL_NVIC_SetPriority(TIM2_IRQn, 3, 0);

        /* Enable the TIMx global Interrupt */
        HAL_NVIC_EnableIRQ(TIM2_IRQn);
    }
    else if(htim->Instance == TIM3)
    {
        /*##-1- Enable peripherals and GPIO Clocks #################################*/
        /* TIMx Peripheral clock enable */
        TIM3_CLK_ENABLE();

        /*##-2- Configure the NVIC for TIMx ########################################*/
        /* Set the TIMx priority */
        HAL_NVIC_SetPriority(TIM3_IRQn, 3, 1);

        /* Enable the TIMx global Interrupt */
        HAL_NVIC_EnableIRQ(TIM3_IRQn);
    }
}

/**
  * @brief  This function handles TIM interrupt request.
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&Tim2Handle);
}

/**
  * @brief  This function handles TIM interrupt request.
  * @param  None
  * @retval None
  */
void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&Tim3Handle);
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM2)
    {
        /*TIM2�û��ж�Ӧ�ó�����������·��հ״�*/
        //========================��TIM2�հ״���ʼ
				//Time2Handler();
				if (timer2Callback != NULL) {
					timer2Callback();
				}
        //��========================TIM2�հ״�����
    }
    else if(htim->Instance == TIM3)
    {
        /*TIM3�û��ж�Ӧ�ó�����������·�*/
        //========================��TIM3�հ״���ʼ
				//Time3Handler();
				if (timer3Callback != NULL) {
					timer3Callback();
				}
        //��========================TIM3�հ״�����
    }

}

void setTimer2Callback(TimerCallback timerCallback){
	timer2Callback = timerCallback;
}

void setTimer3Callback(TimerCallback timerCallback){
	timer3Callback = timerCallback;
}

/********************************END OF FILE********************************/
