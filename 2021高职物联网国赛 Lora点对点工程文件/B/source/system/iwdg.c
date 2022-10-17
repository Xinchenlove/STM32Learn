#include "iwdg.h"
#include "stm32l1xx_hal_iwdg.h"
//#include "sys.h"


IWDG_HandleTypeDef IWDG_Handler; //�������Ź����

//��ʼ���������Ź�
//prer:��Ƶ��:0~7(ֻ�е�3λ��Ч!)
//rlr:�Զ���װ��ֵ,0~0XFFF.
//��Ƶ����=4*2^prer.�����ֵֻ����256!
//rlr:��װ�ؼĴ���ֵ:��11λ��Ч.
//ʱ�����(���):Tout=((4*2^prer)*rlr)/37 (ms).
void IWDG_Init(uint8_t prer,uint16_t rlr)
{
    IWDG_Handler.Instance=IWDG;
    IWDG_Handler.Init.Prescaler=prer;    //����IWDG��Ƶϵ��
    IWDG_Handler.Init.Reload=rlr;        //��װ��
    HAL_IWDG_Init(&IWDG_Handler);
}

//ι�������Ź�
void IWDG_Feed(void)
{
    HAL_IWDG_Refresh(&IWDG_Handler); //��װ��
}
