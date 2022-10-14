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



uint8_t arr[][32] = {
    /*--  ����:  Ԥ  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x42,0x4A,0xD2,0x6A,0x46,0xC0,0x00,0xF2,0x12,0x1A,0xD6,0x12,0x12,0xF2,0x02,0x00,
0x40,0x80,0x7F,0x00,0x01,0x00,0x80,0x4F,0x20,0x18,0x07,0x10,0x20,0x4F,0x80,0x00,

/*--  ����:  ף  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x08,0x08,0x89,0xEE,0x98,0x00,0x7E,0x42,0xC2,0x42,0x42,0xC2,0x42,0x7E,0x00,0x00,
0x02,0x01,0x00,0xFF,0x80,0x43,0x20,0x18,0x07,0x00,0x00,0x3F,0x40,0x40,0x78,0x00,

/*--  ����:  ˳  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x00,0xFE,0x00,0xFC,0x00,0xFF,0x00,0xF2,0x12,0x1A,0xD6,0x12,0x12,0xF2,0x02,0x00,
0x40,0x3F,0x00,0x3F,0x00,0xFF,0x80,0x4F,0x20,0x18,0x07,0x10,0x20,0x4F,0x80,0x00,

/*--  ����:  ��  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x40,0x44,0x44,0x44,0xC4,0xFE,0x42,0x43,0x42,0x00,0xF8,0x00,0x00,0xFF,0x00,0x00,
0x20,0x10,0x0C,0x03,0x00,0xFF,0x01,0x02,0x04,0x00,0x0F,0x40,0x80,0x7F,0x00,0x00,



};

uint8_t State = 0;

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

if(isKey2Pressed()){
    OLED_Clear();
    State = 2;
    resetKey2();
}
if(isKey3Pressed()){
    OLED_Clear();
    State = 3;
    resetKey3();
}
if(isKey4Pressed()){
    OLED_Clear();
    State = 4;
    resetKey4();
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


//��ʾ����

void WZ(uint8_t x,uint8_t y){

    OLED_ShowCHineseArray(x,y,arr[0]);
    OLED_ShowCHineseArray(x+16,y,arr[1]);
    OLED_ShowCHineseArray(x+32,y,arr[2]);
    OLED_ShowCHineseArray(x+48,y,arr[3]);

}

/**
 * Main application entry point.
 */
int main( void )
{
    uint8_t i = 0,F;
    uint32_t t = 0;
    uint8_t  j = 2;

    Init();
    OLED_Init();
    OLED_Clear();
    



    while( 1 )
    {
        
S1:       if(State == 0){
           OLED_Clear();
            OLED_ShowCHineseArray(127-16-i,j,arr[0]);
            if(i > 16){
                OLED_ShowCHineseArray(127-16-i+16,j,arr[1]);
            }
            if(i > 32){
                OLED_ShowCHineseArray(127-16-i+32,j,arr[2]);
            }
            if(i > 48){
                OLED_ShowCHineseArray(127-16-i+48,j,arr[3]);
            }
             HAL_Delay(10);
                i++;
            if(i < 127-16)goto S1;
            State = 1;
        }
        
            

S2:         if(State == 1){
                OLED_Clear();
                if(i < 64){
                    WZ(i,j);
                }else{
                    WZ(127-i,j);
                }

                HAL_Delay(10);
                i++;
                if(i < 127) goto S2;
                i = 0;
            }

S3:         if(State == 2){
                OLED_Clear();
                WZ(127-i,j);    
                 i++;      
                HAL_Delay(10);
                if(i > 128)
                    goto S3;
                 //i = 0;       
                        
            }           
S4:         if(State == 3){
                OLED_Clear();
                WZ(i,j);    
                 i++;      
                HAL_Delay(10);
                if(i < 128)
                    goto S4;
                //i = 0;        
                        
            }

       

S5:         if(State == 4){
                OLED_Clear();
                
                WZ(i,j);    
                    j++;
                HAL_Delay(80);
                
                
                if(j < 8)
                    goto S5;

                    j = 0;
           
            }      
			 //i = 0; 
    }

}