# STM32呼吸灯

**所用库函数**

```c
led_light.h	//呼吸灯必备头文件
setBreathLedArg(64,128);// 设置占空比
switchLed1Breath(); //开启LED1呼吸灯
breathLed();//亮灯
stopLedBreath();switchLed1Breath();//关闭呼吸灯  关闭呼吸灯后再开启呼吸灯
```





## 程序代码

```c
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
#include "led_light.h"	//呼吸灯必备头文件

unsigned char flag = 0;


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
	
		
		flag ++;
		
		resetKey2();
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


/**
 * Main application entry point.
 */
int main( void )
{
    Init();
	//OLED_Init();
	//OLED_Clear();
	setBreathLedArg(64,128);
	switchLed1Breath();
	
    while( 1 )
    {
			KeyDownHandler();
			
			
			if(flag  == 1) breathLed();
			if(flag  == 2) {stopLedBreath();switchLed1Breath();}
			if(flag == 3) {
				breathLed();
			}

			
			
    }
}


```

