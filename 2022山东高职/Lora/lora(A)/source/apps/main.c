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
#include "sht3x.h"
#include "adc_reader.h"
#include "NS_Radio.h"
#include "sx1276.h"

#include "usart1-board.h"

unsigned char Z = 0;
unsigned char State = 0xff;

unsigned char kaiguan[][32] = {
/*--  文字:  开  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x80,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x80,0x00,
0x00,0x80,0x40,0x30,0x0F,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  关  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x10,0x11,0x16,0x10,0x10,0xF0,0x10,0x10,0x14,0x13,0x10,0x00,0x00,0x00,
0x81,0x81,0x41,0x41,0x21,0x11,0x0D,0x03,0x0D,0x11,0x21,0x41,0x41,0x81,0x81,0x00,

};

unsigned char Hxdss[][32] = {
/*--  文字:  呼  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0xFC,0x04,0x04,0xFC,0x00,0x04,0x14,0x64,0x04,0xFE,0x02,0x43,0x32,0x00,0x00,
0x00,0x0F,0x04,0x04,0x0F,0x00,0x01,0x01,0x41,0x81,0x7F,0x01,0x01,0x01,0x01,0x00,

/*--  文字:  吸  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0xFC,0x04,0x04,0xFC,0x02,0x02,0xFE,0x02,0x02,0x62,0x5A,0x46,0xC0,0x00,0x00,
0x00,0x0F,0x04,0x04,0x4F,0x30,0x8E,0x81,0x46,0x28,0x10,0x28,0x46,0x81,0x80,0x00,

/*--  文字:  灯  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x80,0x70,0x00,0xFF,0x20,0x10,0x04,0x04,0x04,0x04,0xFC,0x04,0x04,0x04,0x04,0x00,
0x80,0x60,0x18,0x07,0x08,0x30,0x00,0x00,0x40,0x80,0x7F,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  闪  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0xF8,0x01,0x02,0x00,0x02,0x02,0xF2,0x02,0x02,0x02,0x02,0x02,0xFE,0x00,0x00,
0x00,0xFF,0x00,0x00,0x08,0x04,0x03,0x00,0x01,0x02,0x0C,0x40,0x80,0x7F,0x00,0x00,

/*--  文字:  烁  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x80,0x70,0x00,0xFF,0x20,0x10,0x00,0xFC,0x84,0x84,0xF4,0x82,0x83,0x82,0x80,0x00,
0x80,0x60,0x18,0x07,0x08,0x30,0x20,0x10,0x4C,0x80,0x7F,0x00,0x04,0x08,0x30,0x00,
};

void OLED_State();
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
		if(Z>0){
		
			OLED_Clear();
			Z--;
			OLED_State();
		}

		
		resetKey2();
	}
	if(isKey3Pressed()){
		if(Z < 6){
			OLED_Clear();
			Z++;
			OLED_State();
		}

		resetKey3();
	}
	if(isKey4Pressed()){
		
		State = Z;
		resetKey4();
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


void OLED_State(){

	OLED_ShowChar(128-16,Z*2>6?6:Z*2,'<');

	switch(Z){
		case 0:
		case 1:
		case 2:
		case 3:
			OLED_ShowCHinese(0,0,29);OLED_ShowCHinese(16,0,30);
		OLED_ShowCHinese(0,2,22);OLED_ShowCHinese(16,2,23);
		OLED_ShowCHinese(0,4,24);OLED_ShowCHinese(16,4,23);
		OLED_ShowString(0,6,"LED1");OLED_ShowCHineseArray(32,6,kaiguan[0]);
			
			break;
		case 4:
		OLED_ShowCHinese(0,0,22);OLED_ShowCHinese(16,0,23);
		OLED_ShowCHinese(0,2,24);OLED_ShowCHinese(16,2,23);
		OLED_ShowString(0,4,"LED1");OLED_ShowCHineseArray(32,4,kaiguan[0]);
		OLED_ShowString(0,6,"LED1");OLED_ShowCHineseArray(32,6,kaiguan[1]);
			break;
		case 5:
		OLED_ShowCHinese(0,0,24);OLED_ShowCHinese(16,0,23);
		OLED_ShowString(0,2,"LED1");OLED_ShowCHineseArray(32,2,kaiguan[0]);
		OLED_ShowString(0,4,"LED1");OLED_ShowCHineseArray(32,4,kaiguan[1]);			
	  OLED_ShowString(0,6,"LED2");OLED_ShowCHineseArray(32,6,Hxdss[0]);OLED_ShowCHineseArray(48,6,Hxdss[1]);OLED_ShowCHineseArray(64,6,Hxdss[2]);
			break;
		case 6:
		OLED_ShowString(0,0,"LED1");OLED_ShowCHineseArray(32,0,kaiguan[0]);
		OLED_ShowString(0,2,"LED1");OLED_ShowCHineseArray(32,2,kaiguan[1]);			
	  OLED_ShowString(0,4,"LED2");OLED_ShowCHineseArray(32,4,Hxdss[0]);OLED_ShowCHineseArray(48,4,Hxdss[1]);OLED_ShowCHineseArray(64,4,Hxdss[2]);
    OLED_ShowString(0,6,"LED2");OLED_ShowCHineseArray(32,6,Hxdss[3]);OLED_ShowCHineseArray(48,6,Hxdss[4]);
			break;
		
	
	}
	
}

void State_Send(){
					unsigned char arr[10];
			if(State == 0){

				AdcScanChannel();
				sprintf(arr,"%.2f",AdcReadCh0()*100*5/2.0);
				
			}
		else	if(State == 1){
				float temp,hump;
				call_sht11(&temp,&hump);

				sprintf(arr,"%.2f",temp);
				
			}
		else	if(State == 2){

				float temp,hump;
				call_sht11(&temp,&hump);

				sprintf(arr,"%.2f",hump);			
				
			}
else
	arr[0] = '\0';

				arr[7] = State;
				//arr[7] = Z;
			HAL_Delay(80);
			USART1_SendStr(arr,10);
SX1276Send(arr,10);
			
	
}





/**
 * Main application entry point.
 */
int main( void )
{
    Init();
	OLED_Init();
	OLED_State();
	ADCS_Init();
	USART1_Init(115200);
	AdcScanChannel();
	hal_temHumInit();
	NS_RadioInit(433000521,18,1000,1000);
	
    while( 1 )
    {
			
			KeyDownHandler();
			

			State_Send();
			
			
			
			/*
			unsigned char test[10];
			test[7] = 10;
			SX1276Send(test,10);*/
			
    }
}
