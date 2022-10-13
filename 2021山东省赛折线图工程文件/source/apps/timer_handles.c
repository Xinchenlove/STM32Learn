/* Includes ------------------------------------------------------------------*/
#include "timer_handles.h"
#include "key_scaner.h"

#include "adc_reader.h"
#include "oledfont.h"
#include "hal_oled.h"

void ShowChar1(uint8_t x,uint8_t y,uint8_t chr);
void DrawPoint1(unsigned char x,unsigned char y);
void Fill1(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2);

unsigned int t = 0;

float light[7] ={0,0,0,0,0,0,0};

uint8_t i = 0 ,j = 0;

unsigned char arr[6][10] = {{000}};


void dot_D(uint8_t x,uint8_t y){

	
	DrawPoint1(x,y);
	DrawPoint1(x+1,y);
	DrawPoint1(x-1,y);
	DrawPoint1(x,y+1);
	DrawPoint1(x,y-1);
	
	DrawPoint1(x+1,y+1);
	DrawPoint1(x-1,y-1);
	DrawPoint1(x-1,y+1);
	DrawPoint1(x+1,y-1);

	DrawPoint1(x+1,y+2);
	DrawPoint1(x-1,y-2);
	DrawPoint1(x-1,y+2);
	DrawPoint1(x+1,y-2);

	DrawPoint1(x+2,y+1);
	DrawPoint1(x-2,y-1);
	DrawPoint1(x-2,y+1);
	DrawPoint1(x+2,y-1);

	DrawPoint1(x+2,y);
	DrawPoint1(x-2,y);
	DrawPoint1(x,y+2);
	DrawPoint1(x,y-2);


	



}


void ShowL(uint8_t x,uint8_t y,unsigned char a[]){

	y-=2;
	ShowChar1(x,y,a[0]);
	ShowChar1(x+6,y,a[1]);
	ShowChar1(x+12,y,a[2]);
	/*ShowChar1(x+32,y,arr[n][3]);
	ShowChar1(x+48,y,arr[n][4]);
	ShowChar1(x+72,y,arr[n][5]);*/
	
	

}


void ToPort(uint8_t begin,float high, uint8_t end,float e_high,uint8_t Zifu[]){

		Fill1(begin,high,end,e_high);//连线函数 
		//dot_D(end,e_high);    //画交点函数不写观感好一点
		ShowL(begin,e_high/64*7-1,Zifu);//显示坐标上的值


}

void Time2Handler(){
	keyScanner();
	


	t++;j++;

if(t == 200){i++;
	AdcScanChannel();
	light[6] =  (5/2.0)*(AdcReadCh0()*100);
	

if(i != 6)
light[i] = light[i+1];
	sprintf(arr[i],"%.2f",light[i]);

		
}
if(i == 6){i = 0;
	OLED_Clear();

ToPort(0,(63-(light[0+1]/1000*64)),24,(63-(light[1+1]/1000)*64),arr[0+1]);
ToPort(24,(63-(light[1+1]/1000*64)),48,(63-(light[2+1]/1000)*64),arr[1+1]);
ToPort(48,(63-(light[2+1]/1000*64)),72,(63-(light[3+1]/1000)*64),arr[2+1]);
ToPort(72,(63-(light[3+1]/1000*64)),96,(63-(light[4+1]/1000)*64),arr[3+1]);
ToPort(96,(63-(light[4+1]/1000*64)),120,(63-(light[5+1]/1000)*64),arr[4+1]);


}


	
if(t == 600) {t = 0;}


}

void Time3Handler(){
}

