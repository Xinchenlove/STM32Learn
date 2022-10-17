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
#include "adc_reader.h"
#include "sx1276.h"



uint8_t S = 0,Z = 1;

uint8_t arr[10];

float Zhi[3] = {0};

uint8_t Lamp_s = 0;

uint8_t Json[30];


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


void LED_State();
/**********************************************************************************************
*������void KeyDownHandler( void )
*���ܣ���ť�¼�����
*���룺��
*�������
*����˵������
**********************************************************************************************/
void KeyDownHandler(void) {
	
	if(isKey2Pressed()){
	resetKey2();
		Z--;if(Z == 0)Z = 1;
		
				if(S == 2){Lamp_s =~Lamp_s;
		GpioToggle(&Led1);
		GpioToggle(&Led2);
				}
		OLED_Clear();
		LED_State();
	}
	
	if(isKey3Pressed()){
	resetKey3();
		Z++;if(Z == 4)Z = 3;
		
		OLED_Clear();
		LED_State();
		
	}
	if(isKey4Pressed()){
	resetKey4();
		
		if(S == 0)S = Z;
		else if(S != 0)S = 0;
		
		OLED_Clear();
		LED_State();
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


void LED_State(){
	if(S == 0){
			OLED_ShowString(48,0,"Menu");
		OLED_ShowString(0,2,"1.Auto Lamp");
		OLED_ShowString(0,4,"2.Mula Lamp");
		OLED_ShowString(0,6,"3.View Freq");
		OLED_ShowChar(127-16,2*Z,'<');
	}
	if(S == 1){
	
		OLED_ShowString((127-72)/2,0,"Auto Lamp");
		OLED_ShowString(0,2,"Light:");sprintf(arr,"%.2f",Zhi[0]);
		OLED_ShowString(48,2,arr);
		OLED_ShowString(0,4,"Temp :");sprintf(arr,"%.2f",Zhi[1]);
		OLED_ShowString(48,4,arr);
		OLED_ShowString(0,6,"Humi :");sprintf(arr,"%.2f",Zhi[2]);
		OLED_ShowString(48,6,arr);
	}
	
	
	if(S == 2){
		OLED_ShowString((127-72)/2,0,"Mula Lamp");
		OLED_ShowString(0,2,"Lamp:");
		if(Lamp_s == 0){
			OLED_ShowString(40,2,"Close");
			
		}else 
			OLED_ShowString(40,2,"Open");
		
	}
	
	if(S == 3){
		OLED_ShowString((127-72)/2,0,"View Freq");
		OLED_ShowString(0,2,"Freq:433000521");
		OLED_ShowCHinese(0,4,44);
		
	}

	
}



/**
 * Main application entry point.
 */
int main( void )
{
    Init();
	OLED_Init();
	LED_State();
	hal_temHumInit();
	ADCS_Init();
	NS_RadioInit(433000521,18,1000,1000);
	
    while( 1 )
    {KeyDownHandler();
			
			AdcScanChannel();
			Zhi[0] = AdcReadCh0()*5/2.0*100;
			call_sht11(&Zhi[1],&Zhi[2]);
			
			if((S == 1&& Zhi[0] <= 100)){
				GpioWrite(&Led1,0);
				GpioWrite(&Led2,0);
				Lamp_s = 1;
			}
			else {
				
				if(S == 2){
						//GpioWrite(&Led2,0);
						//GpioWrite(&Led1,0);
				}
				else {
				
					GpioWrite(&Led2,1);
					GpioWrite(&Led1,1);
					Lamp_s = 0;
				}
			}
			

			
			sprintf(Json,"%.2f %.2f %.2f ",Zhi[0],Zhi[1],Zhi[2]);
			
			Json[30-1] = S;
			Json[30-2] = Lamp_s;
			
			
			
			SX1276Send(Json,30);
			
			
		
			
			if(S == 1)LED_State();
			
			
    }
}
