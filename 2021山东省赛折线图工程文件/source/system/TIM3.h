#ifndef _TIM3_H
#define _TIM3_H
#include "board.h"
#include "usart2-board.h"
#include "usart1-board.h"


extern TIM_HandleTypeDef TIM3_Handler;      //��ʱ��3PWM��� 

void TIM3_Init(uint16_t arr,uint16_t psc);    //��ʱ����ʼ��
#endif

