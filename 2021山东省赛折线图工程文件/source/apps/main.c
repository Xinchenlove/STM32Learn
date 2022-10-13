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
#include "oledfont.h"
#include "hal_oled.h"






void ShowChar1(uint8_t x,uint8_t y,uint8_t chr);
void DrawPoint1(unsigned char x,unsigned char y);
void Fill1(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2);


/**********************************************************************************************
*������void Init( void )
*���ܣ�ƽ̨��ʼ��
*���룺��
*�������
*����˵������
**********************************************************************************************/
void Init() {
    // ������ƽ̨��ʼ��
    BoardInitMcu();
    BoardInitPeriph();
    keys_init();//������ʼ��
    setTimer2Callback(Time2Handler);
    Tim2McuInit(1);//��ʱ����ʼ�������ö�ʱ�ж�1ms�ж�һ��
	 
}

/**********************************************************************************************
*������void KeyDownHandler( void )
*���ܣ���ť�¼�����
*���룺��
*�������
*����˵������
**********************************************************************************************/
void KeyDownHandler(void) {
	
}

/**********************************************************************************************
*������void handlerPre10Ms( void )
*���ܣ�10����ѭ��
*���룺��
*�������
*����˵����ѭ��������ʱ��300ms
**********************************************************************************************/
void handlerPre10Ms(void) {
    for (int delay = 0; delay < 30; delay++) {
        HAL_Delay(10);
        
    }
}
void dot_D(uint8_t x,uint8_t y);

/**
 * Main application entry point.
 */
int main( void )
{
Init();

ADCS_Init();

uint8_t arr[5] = {'\0'};
    OLED_Init();
    OLED_Clear();


    while( 1 )
    {

       

        


    }
}


void ShowChar1(uint8_t x,uint8_t y,uint8_t chr)
{      	
	unsigned char c=0,i=0;	
	c=chr-' ';		
	if(x>Max_Column-1){x=0;y=y+2;}

		OLED_Set_Pos(x,y+1);
		for(i=0;i<6;i++)
			OLED_WR_Byte(F6x8[c][i],OLED_DATA);
	
}







void DrawPoint1(unsigned char x,unsigned char y)
{
       static unsigned char data1;
       data1=(unsigned char)(0x01<<((y%8)));
       OLED_Set_Pos(x, (unsigned char)(y >> 3));
       OLED_WR_Byte((unsigned char)(0xb0 + (y >> 3)),0);
       OLED_WR_Byte((unsigned char)(((x & 0xf0) >> 4) | 0x10),0);
       OLED_WR_Byte((unsigned char)((x & 0x0f) | 0x00),0);
       OLED_WR_Byte(data1,1);
}





void Fill1(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2) //只可以花45°的线，会有点小bug但够用
{

while(1){
    if(x1<x2)
        x1 ++;
    if(x1>x2)    
        x2 --;
    if(y1<y2)
        y1++;
    if(y1>y2)
        y1--;

        DrawPoint1(x1,y1);
    /* DrawPoint1(x1,y1-1);
        DrawPoint1(x1-1,y1);*/ //加粗线条偶尔加粗

    if(y1 == y2&&x1 == x2)break;
    }
}




    if(y1 == y2&&x1 == x2)break;
    }
}
