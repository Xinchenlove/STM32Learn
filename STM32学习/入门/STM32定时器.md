# STM32定时器

**STM32的定时器2和定时器3**

```c
setTimer2Callback(Time2Handler);//初始化定时器二
setTimer3Callback(Time3Handler);//初始化定时器三
Tim2McuInit(1);//设置定时器二1ms中断一次
Tim3McuInit(4);//设置定时器三1ms中断一次
//在屏幕中时时显示毫秒导致定时器不准确
```

定时器代码在`#include "timer_handles.h"`中





## 代码

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


/**
 * Main application entry point.
 */
int main( void )
{
    Init();
	OLED_Init();
	OLED_Clear();
	
setTimer3Callback(Time3Handler);//初始化定时器三
Tim3McuInit(4);//设置定时器三延时1ms
	
	
    while( 1 )
    {
	
			GpioWrite(&Led2,1);//LED2灭
			GpioWrite(&Led1,0);//LED1亮
			HAL_Delay(1000);//延时1m
			GpioWrite(&Led1,1);//LED1灭
			GpioWrite(&Led2,0);//LED2亮
			HAL_Delay(1000);//延时1m
			
    }
}

```

## 定时器代码

```c
/* Includes ------------------------------------------------------------------*/
#include "timer_handles.h"
#include "key_scaner.h"

void Time2Handler(){
	//keyScanner();
	
	
	
static unsigned int ms = 0;	
static unsigned int m = 0;		
static unsigned int M = 0;	
	ms++;
	if(ms == 1000){
	
		ms = 0;
		m++;

		unsigned char  arr[30] = {'\0'};
		sprintf(arr,"%d:%d:%d",M, m ,ms);	
		OLED_ShowString(16,0,arr);
	}
	if(m == 60){
		m = 0;
		M++;
		
		
	}

	
	
	
}

void Time3Handler(){

static unsigned int ms = 0;	
static unsigned int m = 0;		
static unsigned int M = 0;	
	ms++;
	if(ms == 1000){
	
		ms = 0;
		m++;	
	unsigned char  arr[30] = {'\0'};
	sprintf(arr,"%d:%d:%d",M, m ,ms);
	OLED_ShowString(16,2,arr);
	}
	if(m == 60){
		m = 0;
		M++;
	}

	
	
}

```

