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

#include "sx1276.h"
#include "NS_Radio.h"

uint8_t arr[10];
uint8_t Z = 0,S = 0;//ָ��λ��
uint8_t state = 0x00;//����LED��״̬

uint8_t SE[] = {//���Ǳ�־
/*--  ???????:C:\Users\Newland\Desktop\??????.bmp  --*/
/*--  ??x??=16x16  --*/
0x00,0x00,0x80,0xE0,0xE0,0xFC,0xFE,0xFE,0xFE,0xFC,0xF0,0xE0,0x80,0x00,0x00,0x00,
0x30,0x7C,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7E,0x78,0x00,
};
uint8_t KG[][32]= {//����
/*--  ??:  ?  --*/
/*--  ??12;  ??????????:?x?=16x16   --*/
0x80,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x80,0x00,
0x00,0x80,0x40,0x30,0x0F,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,

/*--  ??:  ?  --*/
/*--  ??12;  ??????????:?x?=16x16   --*/
0x00,0x00,0x10,0x11,0x16,0x10,0x10,0xF0,0x10,0x10,0x14,0x13,0x10,0x00,0x00,0x00,
0x81,0x81,0x41,0x41,0x21,0x11,0x0D,0x03,0x0D,0x11,0x21,0x41,0x41,0x81,0x81,0x00,

};








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
	if(isKey2Pressed()){// LED1 �� �� LED2 �� �� LED2 �� �� LED1 �� �� LED1��
		Z+=3;
		resetKey2();
		OLED_Clear();
			if(Z == 6)Z = 2;
        if(Z == 5)Z = 1;
        if(Z == 4)Z = 0;
		
	}
	if(isKey3Pressed()){
		Z++;
		resetKey3();
		OLED_Clear();
		if(Z == 4)Z = 0;
	}
	if(isKey4Pressed()){
	
		resetKey4();
		OLED_Clear();
		
		if(Z == 0){
				state |= 0x0F;
		}
		if(Z == 1){
				state &=~0x0F;
		}
		
		if(Z == 2){
				state |= 0xF0;
		}
		if(Z == 3){
				state &=~0xF0;
		}
		
	}	
	
	
	
	
	
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





void OLED_State(){
	OLED_ShowString(0,0,"LED1:");
	OLED_ShowCHineseArray(48,0,KG[0]);
	OLED_ShowCHineseArray(80,0,KG[1]);
	OLED_ShowString(0,4,"LED2:");
	OLED_ShowCHineseArray(48,4,KG[0]);
	OLED_ShowCHineseArray(80,4,KG[1]);
	OLED_DrawBMP(48+(Z%2 == 0?0:32),2+(Z>=2?4:0),16,16,SE);
	
}









/**
 * Main application entry point.
 */
int main( void )
{
    Init();
	OLED_Init();
	NS_RadioInit(433000001,16,1000,1000);
	
    while( 1 )
    {
			SX1276Send(&state,1);
			KeyDownHandler();
			OLED_State();
			
    }
}
