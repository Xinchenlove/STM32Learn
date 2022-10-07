单联继电器-- 双联继电器同理

```c
GpioInit()   //Gpio初始化
GpioInit( &Relay1, Relay_1, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0 ); //GPIO初始化，继电器的引脚是PB2
GpioWrite(&Relay1,1);// 打开继电器1
GpioWrite(&Relay1,0);// 关闭继电器1
GpioToggle(&Relay1);//翻转电平

//使用继电器要在main.c加
#define Relay_1   PB_2	//继电器1的引脚是PB2(单联继电器)
#define Relay_2   PB_0	//继电器2的引脚是PB0
```

火焰传感器    触发为高电平

```c
HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);	//火焰传感器的引脚是PA0(ADC0)  使用火焰传感器一定关闭ADC初始化
```

人体红外传感器  触发为高电平

```c
HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2); //人体红外传感器的引脚是PA2
```

**ADC传感器计算实际值**

1.光照传感器（单位 ： Lux）

​	光照值 = (5/2.0) * (电压值 * 100)

2.空气质量 (单位：ug/m3)

​	空气质量 = 10 ^((0.2552-lg电压值)/0.5829)

3.可燃气体传感器(单位：PPM)

​	可燃气体 = 10 ^ ( ( 1.395- lg( ( 50 / 电压值 - 20 ) / 10 ) ) / 0.465 );

例：

```c
//获取光照值
//在头文件引用#include "adc_reader.h"才可以

#include "adc_reader.h"

int main( void )
{
    Init();
	ADCS_Init();//初始化ADC
	OLED_Init();//初始化OLED
    while( 1 )
    {
			
			AdcScanChannel();//转换ADC数据为电压值
			float l = AdcReadCh0();//获取电压值
			unsigned char  arr[20];
			sprintf(arr,"lignt = %.2f",5/2.0*(l*100)); // 光照转换公式
			OLED_ShowString(0,0,arr); //显示 
		
			
			
			
			
    }
}
```

