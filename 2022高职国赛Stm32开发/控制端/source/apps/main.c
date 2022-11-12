/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  */
#include <string.h>
#include "board.h"
#include "hal_key.h"
#include "tim-board.h"
#include "timer_handles.h"
#include "NS_Radio.h"

#include "usart1-board.h"

#define Relay1 PB_2
Gpio_t Relay;







unsigned char Fun_State = 0;





/**********************************************************************************************
*函数：void Init( void )
*功能：平台初始化
*输入：无
*输出：无
*特殊说明：无
**********************************************************************************************/
void Init() {
    // 开发板平台初始化
    BoardInitMcu();
    BoardInitPeriph();
    keys_init();//按键初始化
    setTimer2Callback(Time2Handler);
    Tim2McuInit(1);//定时器初始化，设置定时中断1ms中断一次
	 
}

/**********************************************************************************************
*函数：void KeyDownHandler( void )
*功能：按钮事件监听
*输入：无
*输出：无
*特殊说明：无
**********************************************************************************************/
void KeyDownHandler(void) {
	
	if(isKey2Pressed()){
			resetKey2();
		Fun_State = 1;
		
	}
	
	if(isKey3Pressed()){
			resetKey3();
		Fun_State = 0;
	}
}

/**********************************************************************************************
*函数：void handlerPre10Ms( void )
*功能：10毫秒循环
*输入：无
*输出：无
*特殊说明：循环处理总时长300ms
**********************************************************************************************/
void handlerPre10Ms(void) {
    for (int delay = 0; delay < 30; delay++) {
        HAL_Delay(10);
        
    }
}


unsigned char LED_R[] = {0xA5,0x06,0x00,0xA0,0xFF,0x00,0x00,0xEE,0x5A};
unsigned char LED_G[] = {0xA5,0x06,0x00,0xA0,0x00,0xFF,0x00,0xEE,0x5A};
unsigned char LED_B[] = {0xA5,0x06,0x00,0xA0,0x00,0x00,0xFF,0xEE,0x5A};
unsigned char LED_C[] = {0xA5,0x06,0x00,0xA0,0x00,0x00,0x00,0xEE,0x5A};
	

void OLED_State(unsigned char Read[4]){
	
unsigned char arr[20];
	HAL_Delay(100);
	OLED_ShowString(0,0,"R:");sprintf(arr,"%d  ",Read[0]);OLED_ShowString(16,0,arr);
	OLED_ShowString(0,2,"G:");sprintf(arr,"%d  ",Read[1]);OLED_ShowString(16,2,arr);
	OLED_ShowString(0,4,"B:");sprintf(arr,"%d  ",Read[2]);OLED_ShowString(16,4,arr);
	if(Read[0] == 0xff){
		
		USART1_SendStr(LED_R,9);
	}
	else if(Read[1] == 0xff){
	
		USART1_SendStr(LED_G,9);
	}
	else if(Read[2] == 0xff){
	
		USART1_SendStr(LED_B,9);
	}else 
	{
		USART1_SendStr(LED_C,9);
	}
	
}






/**
 * Main application entry point.
 */
int main( void )
{
	
    Init();
	OLED_Init();
	USART1_Init(9600);
	
	GpioInit(&Relay,Relay1,PIN_OUTPUT,PIN_PUSH_PULL,PIN_NO_PULL,0);
	GpioWrite(&Relay,0);
		NS_RadioInit(433000520,18,1000,1000);
    
	while( 1 )
    {
			KeyDownHandler();
			
	unsigned char Read[4];
			ReadRadioRxBuffer(Read);
			
			OLED_State(Read);
			if(Read[3] == 1){
				GpioWrite(&Led1,0);
				GpioWrite(&Led2,0);
			}else {
				GpioWrite(&Led1,1);
				GpioWrite(&Led2,1);			
			}
			
			if(Fun_State == 1){
				OLED_ShowString(0,6,"Fun:On ");
				GpioWrite(&Relay,1);
			}
			else {
				OLED_ShowString(0,6,"Fun:Off");
				GpioWrite(&Relay,0);
			}
			
			
			
			
    }
}
