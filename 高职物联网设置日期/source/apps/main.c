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

#include "flash.h"


#define ADDRESS1 0x800D000




uint8_t DQRQ[][32] = {
    /*--  文字:  当  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x40,0x42,0x44,0x58,0x40,0x40,0x7F,0x40,0x40,0x50,0x48,0xC6,0x00,0x00,0x00,
0x00,0x40,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0xFF,0x00,0x00,0x00,

/*--  文字:  前  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x08,0x08,0xE8,0x29,0x2E,0x28,0xE8,0x08,0x08,0xC8,0x0C,0x0B,0xE8,0x08,0x08,0x00,
0x00,0x00,0xFF,0x09,0x49,0x89,0x7F,0x00,0x00,0x0F,0x40,0x80,0x7F,0x00,0x00,0x00,

/*--  文字:  日  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x00,0xFE,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0xFE,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xFF,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0xFF,0x00,0x00,0x00,0x00,

/*--  文字:  期  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x04,0xFF,0x24,0x24,0x24,0xFF,0x04,0x00,0xFE,0x22,0x22,0x22,0xFE,0x00,0x00,
0x88,0x48,0x2F,0x09,0x09,0x19,0xAF,0x48,0x30,0x0F,0x02,0x42,0x82,0x7F,0x00,0x00,


};

uint8_t NYR[][32] = {
    /*--  文字:  年  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x20,0x18,0xC7,0x44,0x44,0x44,0x44,0xFC,0x44,0x44,0x44,0x44,0x04,0x00,0x00,
0x04,0x04,0x04,0x07,0x04,0x04,0x04,0x04,0xFF,0x04,0x04,0x04,0x04,0x04,0x04,0x00,

/*--  文字:  月  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x00,0xFE,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0xFE,0x00,0x00,0x00,
0x80,0x40,0x30,0x0F,0x02,0x02,0x02,0x02,0x02,0x02,0x42,0x82,0x7F,0x00,0x00,0x00,

/*--  文字:  日  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x00,0xFE,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0xFE,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xFF,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0xFF,0x00,0x00,0x00,0x00,
};

uint8_t JT[] = {
    /*--  调入了一幅图像：C:\Users\Newland\Pictures\image.bmp  --*/
/*--  宽度x高度=16x16  --*/
0x80,0x80,0xC0,0xC0,0xE0,0xE0,0xF0,0xF8,0xF8,0xFC,0xFC,0xFE,0xFF,0xFF,0x00,0x00,
0x01,0x01,0x03,0x03,0x07,0x07,0x0F,0x1F,0x1F,0x3F,0x3F,0x7F,0xFF,0xFF,0x00,0x00,
};

uint8_t Page = 1;
uint8_t  A = 1;

uint32_t DATE[3] = {2022,10,15};

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
uint8_t DAY[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

void DATATIME(){

    if(DATE[1] == 13) DATE[1] = 12;
    if(DATE[1] == 0) DATE[1]  = 1;
    if(DAY[DATE[1]] == DATE[2]-1) DATE[2] = DAY[DATE[1]];
    if(DATE[2] == 0)DATE[2] = 1;
    
    /*//想多了 笑死 根本就不需要判断  -_-
    if(DATE[0]%400 == 0||DATE[0]%100!=0&&DATE[0]%4 == 0){

        if(DAY[DATE[1]]==DATE[2]-1){
            DATE[1]++;
            DATE[2] = 1;
        }
        if(DATE[2] == 0){
            DATE[1]--;
            DATE[2] = DAY[DATE[2]];
        }
    }else {

    if(DAY[DATE[1]]==DATE[2]-1){
		DATE[1]++;
		DATE[2] = 1;
	}
	if(DATE[2] == 0){
		DATE[1]--;
		DATE[2] = DAY[DATE[2]];
	}

    }
    */


}
    



void KeyDownHandler(void) {

if(Page!=1){
        if(isKey2Pressed()){
            OLED_Clear();
            resetKey2();

        if(Page == 3){
        if(A == 1)DATE[0]--;
        if(A == 2)DATE[1]--;
        if(A == 3)DATE[2]--;
DATATIME();



        OLED_ShowNum(32,2,DATE[0],4,16);
        OLED_ShowNum(32,4,DATE[1],2,16);
        OLED_ShowNum(32,6,DATE[2],2,16);
        } else
                A--;
            if(A == 0)A = 3;

        
            
        }
        if(isKey3Pressed()){
            OLED_Clear();
            resetKey3();
            
            if(Page == 3){

    if(A == 1)DATE[0]++;
    if(A == 2)DATE[1]++;
    if(A == 3)DATE[2]++;
DATATIME();
    OLED_ShowNum(32,2,DATE[0],4,16);
    OLED_ShowNum(32,4,DATE[1],2,16);
    OLED_ShowNum(32,6,DATE[2],2,16);
            }
            else
                A++;
                
            if(A == 4)A = 1;
        }
    }


    if(isKey4Pressed()){
        OLED_Clear();
        resetKey4();
        Page ++;if(Page == 5)Page = 2;

    }

    if(Page == 4){

        STMFLASH_Write(ADDRESS1,DATE,3);
        Page = 2;
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



void ShowPage1(){

    OLED_ShowCHineseArray(0,0,DQRQ[0]);
    OLED_ShowCHineseArray(16,0,DQRQ[1]);
    OLED_ShowCHineseArray(32,0,DQRQ[2]);
    OLED_ShowCHineseArray(48,0,DQRQ[3]);

    OLED_ShowChar(64,0,':');
    OLED_ShowNum(0,4,DATE[0],4,16);OLED_ShowCHineseArray(40,4,NYR[0]);
    OLED_ShowNum(0,6,DATE[1],2,16);OLED_ShowCHineseArray(24,6,NYR[1]);
    OLED_ShowNum(48,6,DATE[2],2,16);OLED_ShowCHineseArray(72,6,NYR[2]);


}

void ShowPage2(){

    OLED_ShowCHineseArray(0,2,NYR[0]);OLED_ShowChar(16,2,':');OLED_ShowNum(32,2,DATE[0],4,16);
    OLED_ShowCHineseArray(0,4,NYR[1]);OLED_ShowChar(16,4,':');OLED_ShowNum(32,4,DATE[1],2,16);
    OLED_ShowCHineseArray(0,6,NYR[2]);OLED_ShowChar(16,6,':');OLED_ShowNum(32,6,DATE[2],2,16);
    OLED_DrawBMP(127-32,2*A,16,16,JT);

    if(Page == 3){
        OLED_ShowChar(127-16,2*A,'@');
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
   
    STMFLASH_Read(ADDRESS1,DATE,3);
    
    ShowPage1();
    while( 1 )
    {
        KeyDownHandler();
        if(Page != 1){

            ShowPage2();

        }

			
    }
}
