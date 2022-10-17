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

#define Relay_1   PB_2	
Gpio_t Relay1;


uint8_t S = 1,Z = 1;

uint8_t arr[10];



uint8_t Lamp_s = 0;


uint8_t Zhi[3][10];

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

void LED_State(){
	if(S == 0){
			OLED_ShowString((128-88)/2,0,"Select Menu");
			OLED_ShowCHinese((128-16)/2,4,44);
	}
	if(S == 1){
	
		OLED_ShowString((127-72)/2,0,"Auto Lamp");
		OLED_ShowString(0,2,"Light:");sprintf(arr,"%s",Zhi[0]);
		OLED_ShowString(48,2,arr);
		OLED_ShowString(0,4,"Temp :");sprintf(arr,"%s",Zhi[1]);
		OLED_ShowString(48,4,arr);
		OLED_ShowString(0,6,"Humi :");sprintf(arr,"%s",Zhi[2]);
		OLED_ShowString(48,6,arr);
	}
	
	
	if(S == 2){
		OLED_ShowString((127-72)/2,0,"Mula Lamp");
		OLED_ShowString(0,2,"Lamp:");
		if(Lamp_s == 0){
			OLED_ShowString(40,2,"Close");
		
			
		}else 
			OLED_ShowString(40,2," Open");

	}
	
	if(S == 3){
		OLED_ShowString((127-72)/2,0,"View Freq");
		OLED_ShowString(0,2,"Freq:433000521");
		
	}

	
}



/**
 * Main application entry point.
 */
int main( void )
{
    Init();
	OLED_Init();
	GpioInit( &Relay1, Relay_1, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0 );
		NS_RadioInit(433000521,18,1000,1000);
	uint8_t Json[30];
    while( 1 )
    {
			ReadRadioRxBuffer(Json);
			if(S != Json[30-1])OLED_Clear();
			S = Json[30-1];
			Lamp_s  =  Json[30-2];
			uint8_t i,j,t = 0;
			
			
			if(S == 1)
					for(i = 0,j = 0;i < 28;i ++){
						if(Json[i] != ' '){
							Zhi[j][t] = Json[i];	
							t++;
						}else {j++;t = 0;}
						if(j == 3)break;
					}
					
if(Lamp_s == 0){

			GpioWrite(&Led1,1);
			GpioWrite(&Led2,1);
	GpioWrite(&Relay1,1);
	
}else {

			GpioWrite(&Led1,0);
			GpioWrite(&Led2,0);
	GpioWrite(&Relay1,0);
}
	
			LED_State();
			
			//OLED_ShowString(0,0,Json);
    }
}
