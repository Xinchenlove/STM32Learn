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
#include "adc_reader.h"
#include "sht3x.h"
#include "NS_Radio.h"
#include "sx1276.h"

#include "usart1-board.h"

/*************************    va   *********************************************/
float temp,hump,light;

unsigned char State = 0;
unsigned char Send[5];


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
		Send[0] = 0xff;
		Send[1] = 0x00;
		Send[2] = 0x00;
		SX1276Send(Send,4);
	}
	if(isKey3Pressed()){
		resetKey3();
		Send[0] = 0x00;
		Send[1] = 0xff;
		Send[2] = 0x00;
	SX1276Send(Send,4);
	}
	if(isKey4Pressed()){
		resetKey4();
		Send[0] = 0x00;
		Send[1] = 0x00;
		Send[2] = 0xff;
	SX1276Send(Send,4);
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


void OLED_State (){
	
	if(State == 0){
unsigned char arr[30];
	sprintf(arr,"%.2f *%.2f *%.2f   *",temp,hump,light);
	unsigned char Zhi[3][10];
	unsigned char i = 0,j = 0,i0 = 0;
	while(j<3){
		
		if(arr[i] != '*'){
			
			Zhi[j][i0] = arr[i];
			i0++;
			
		}else {
			j++;
			i0 = 0;
			
		}
		
		i++;
	}
	
	if(light < 200){
		GpioWrite(&Led1,0);
		GpioWrite(&Led2,0);
		Send[3] = 1;
		SX1276Send(Send,5);
	}else {
		GpioWrite(&Led1,1);
		GpioWrite(&Led2,1);
		Send[3] = 0;
		SX1276Send(Send,5);
	
	}
	
		HAL_Delay(20);
		OLED_ShowString(0,0," Temp:");OLED_ShowString(48,0,Zhi[0]);
		OLED_ShowString(0,2," Hump:");OLED_ShowString(48,2,Zhi[1]);
		OLED_ShowString(0,4,"Light:");OLED_ShowString(48,4,Zhi[2]);
	
	USART1_SendStr(arr,30);//发送到安卓客户端
	}
	
}






/**
 * Main application entry point.
 */
int main( void )
{
    Init();
	ADCS_Init();
hal_temHumInit();
	
	OLED_Init();
	
	USART1_Init(9600);
	
	NS_RadioInit(433000520,18,1000,1000);
    while( 1 )
    {
			AdcScanChannel();
			light = AdcReadCh0()*5/2.0*100;
			call_sht11(&temp,&hump);
			OLED_State ();
			
			
			KeyDownHandler();
			
			
			
    }
}
