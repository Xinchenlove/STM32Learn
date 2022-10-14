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


/*---------------------------------------------------------------------------------------------*/



//32*32
uint8_t Weixiao[] = {
0x00,0x00,0x80,0xC0,0xF0,0xF0,0x78,0x3C,0x3C,0x1E,0x0F,0x0F,0x0F,0x0F,0x07,0x07,
0x07,0x07,0x0F,0x0F,0x0F,0x0F,0x1E,0x3C,0x3C,0x78,0xF0,0xF0,0xC0,0xC0,0x00,0x00,
0xFC,0xFE,0xFF,0x3F,0x03,0x01,0x00,0x00,0x1F,0x3F,0x3F,0x3F,0x1F,0x0E,0x00,0x00,
0x00,0x00,0x0E,0x1F,0x3F,0x3F,0x3F,0x1F,0x00,0x00,0x01,0x03,0x3F,0xFF,0xFE,0xFC,
0x3F,0x7F,0xFF,0xFC,0xC0,0x80,0x00,0x00,0x1C,0x7C,0xFC,0xF8,0xE0,0xC0,0xC0,0xC0,
0xC0,0xC0,0xC0,0xE0,0xF8,0xFC,0x7C,0x1C,0x00,0x00,0x80,0xC0,0xFC,0xFF,0x7F,0x3F,
0x00,0x00,0x01,0x03,0x0F,0x0F,0x3E,0x3C,0x3C,0x78,0xF0,0xF0,0xF1,0xF3,0xE3,0xE3,
0xE3,0xE3,0xF3,0xF1,0xF0,0xF0,0x78,0x3C,0x3C,0x3E,0x0F,0x0F,0x03,0x03,0x00,0x00
};

uint8_t buxiao[] = {
0x00,0x00,0x80,0xC0,0xF0,0xF0,0x78,0x3C,0x1C,0x1E,0x0E,0x0F,0x07,0x07,0x07,0x07,
0x07,0x07,0x07,0x07,0x0F,0x0E,0x1E,0x1C,0x3C,0x78,0xF0,0xF0,0xC0,0x80,0x00,0x00,
0xF8,0xFE,0xFF,0x0F,0x03,0x00,0x00,0x00,0x1E,0x1F,0x3F,0x3F,0x1F,0x0C,0x00,0x00,
0x00,0x00,0x0C,0x1F,0x3F,0x3F,0x1F,0x1E,0x00,0x00,0x00,0x03,0x0F,0xFF,0xFE,0xF8,
0x1F,0x7F,0xFF,0xF0,0xC0,0x00,0x00,0x00,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x10,0x00,0x00,0xC0,0xF0,0xFF,0x7F,0x1F,
0x00,0x00,0x01,0x03,0x0F,0x0F,0x1E,0x3C,0x38,0x78,0x70,0xF0,0xE0,0xE0,0xE0,0xE0,
0xE0,0xE0,0xE0,0xE0,0xF0,0x70,0x78,0x38,0x3C,0x1E,0x0F,0x0F,0x03,0x01,0x00,0x00
};

uint8_t bukaixin[] = {
0x00,0x00,0x80,0xC0,0xF0,0xF0,0x78,0x3C,0x1E,0x1E,0x0E,0x0F,0x0F,0x07,0x07,0x07,
0x07,0x07,0x07,0x0F,0x0F,0x0E,0x1E,0x1E,0x3C,0x78,0xF8,0xF0,0xE0,0x80,0x00,0x00,
0xF8,0xFF,0xFF,0x1F,0x03,0x00,0x00,0x00,0x1E,0x3F,0x3F,0x3F,0x1F,0x0E,0x00,0x00,
0x00,0x00,0x0C,0x1F,0x3F,0x3F,0x3F,0x1E,0x00,0x00,0x00,0x03,0x1F,0xFF,0xFF,0xF8,
0x1F,0xFF,0xFF,0xF8,0xC0,0x00,0x00,0x02,0x02,0xE0,0xF0,0xF8,0x3C,0x1C,0x1E,0x0E,
0x0E,0x1C,0x1C,0x7C,0xF8,0xF0,0xC0,0x02,0x00,0x00,0x00,0xC0,0xF8,0xFF,0xFF,0x1F,
0x00,0x00,0x01,0x07,0x0F,0x1F,0x1E,0x3C,0x78,0x78,0x70,0xF0,0xF0,0xE0,0xE0,0xE0,
0xE0,0xE0,0xE0,0xF0,0xF0,0x70,0x78,0x78,0x3C,0x1E,0x1F,0x0F,0x07,0x01,0x00,0x00
};


//40*35
uint8_t Mxin[] = {
0xE0,0xF8,0xFC,0xFE,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
0xFE,0xFC,0xF8,0xF0,0xF0,0xF8,0xFC,0xFE,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFE,0xFE,0xFC,0xF8,0xE0,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,
0x00,0x00,0x03,0x07,0x0F,0x1F,0x1F,0x3F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x7F,0x3F,0x1F,0x0F,0x07,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0x01,0x03,0x07,0x1F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,
0x3F,0x1F,0x0F,0x07,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x07,0x07,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
//32*29
uint8_t mxin[] = {
0xF0,0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xFC,0xF8,
0xF8,0xFC,0xFE,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFC,0xF8,0xF0,
0x0F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0x0F,
0x00,0x00,0x00,0x00,0x01,0x03,0x03,0x07,0x0F,0x0F,0x1F,0x3F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0x1F,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x1F,0x0F,
0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

uint8_t BQ[][32] = {
    /*--  文字:  表  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x04,0x24,0x24,0x24,0x24,0x24,0xFF,0x24,0x24,0x24,0x24,0x24,0x04,0x00,0x00,
0x21,0x21,0x11,0x09,0xFD,0x83,0x41,0x23,0x05,0x09,0x11,0x29,0x25,0x41,0x41,0x00,

/*--  文字:  情  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0xE0,0x00,0xFF,0x10,0x64,0x54,0x54,0x54,0x7F,0x54,0x54,0x54,0x44,0x40,0x00,
0x01,0x00,0x00,0xFF,0x00,0x00,0xFF,0x15,0x15,0x15,0x55,0x95,0x7F,0x00,0x00,0x00,
};


uint8_t OLED_State = 0;
uint8_t Page = 1;


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
            OLED_State = 0;
            OLED_Clear();
            resetKey2();
        }
        if(isKey3Pressed()){
            OLED_State = 1;
            OLED_Clear();
            resetKey3();
        }

        if(isKey4Pressed()){
                resetKey4();
                Page++;
                OLED_Clear();
            } if(Page == 4)Page = 1;







	
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

void Xintiao(uint32_t hz){
static uint32_t t = 0;

    if(t == 0){
    OLED_Clear();
    OLED_DrawBMP(48,2,32,32,mxin);
            GpioWrite(&Led1,1);
            GpioWrite(&Led2,0);
    }
    HAL_Delay(1);
    t++;
    if(t > hz/2&&t < hz){
         OLED_DrawBMP(44,1,40,40,Mxin);
        GpioWrite(&Led1,0);
        GpioWrite(&Led2,1);
    }
    if(t > hz)
    t = 0;

}

    uint8_t arr[10]  ={'\0'};
    uint8_t H=12,M=0,S=0;
    uint32_t MS = 0;
void time(){




            HAL_Delay(1);
            MS++;
            if(MS == 100){S++;MS = 0;}
            if(S == 60){M++;S = 0;}
            if(M == 60){H++;M = 0;}
            if(H == 24)H = 0;
            sprintf(arr,"%02d:%02d:%02d",H,M,S);

}

/**
 * Main application entry point.
 */
int main( void )
{

    Init();
    OLED_Init();
    OLED_Clear();
    ADCS_Init();

    while( 1 )
    {
        time();
KeyDownHandler();

        if(OLED_State == 0){// A页面
            GpioWrite(&Led1,0);GpioWrite(&Led2,0);

            OLED_ShowString(64,0,arr);


                switch(Page){

                    case 1:OLED_DrawBMP(48,2,32,32,Weixiao);
                    break;
                    case 2:OLED_DrawBMP(48,2,32,32,buxiao);
                    break;
                    case 3:OLED_DrawBMP(48,2,32,32,bukaixin);
                    break;

                }
            OLED_ShowCHineseArray(48,6,BQ[0]);OLED_ShowCHineseArray(64,6,BQ[1]);
            
            }else { //B页面

            AdcScanChannel();
            float L = (5/2.0)*AdcReadCh0()*100;//光照值转换公式
            sprintf(arr,":%.2fLux",L);
            OLED_ShowCHinese(16,6,29);OLED_ShowCHinese(32,6,30);OLED_ShowString(48,6,arr);//显示中文输出光照值
            Xintiao(10+L);//心跳频率
            /*
            //题目要求
            if(L>100){
                Xintiao(500);
            }else
            Xintiao(100);
            */

            
            }
			

    }
}
