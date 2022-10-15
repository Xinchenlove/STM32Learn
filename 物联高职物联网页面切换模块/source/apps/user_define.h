#ifndef _USER_DEFINE_H_
#define _USER_DEFINE_H_

#include <stdbool.h>

//OLED��ʾ�����
#define USE_OLED_RST 				false 	//û��ʹ�õ�OLED��ʾ����RST��λ��

//LED�����
#define USE_LED3_TO_LED4 			false

//LORAģ�����
#define USE_SX1276_RESET 			false 	//û��ʹ�ø�����
#define USE_SX1276_DIO2_TO_DIO5 	false 	//û��ʹ��SX_1276��DIO2��DIO5������
#define	USE_SX1276_RXTX 			false 	//û��ʹ�ø�����
#define USE_RADIO_ANT_SWITCH 		false

//LORAģ��SX1276/1278�Ĵ����������

//������
#define USE_BATTERY 				false

//���Է������
#define ENGINEER_DEBUG 				false	//������Ϣ���أ�trueʱ���ӡprintf������
#define USE_PIN_NC 					false
#define NEWLAND_ACCELERATE_DEBUG	true	//���ٷ���ʱ��
#define NEWLAND_USE_RX_TX_RF_SET	true	//�����շ�����ʹ���´�½����
#define NEWLAND_EXHIBITION			true	//չʾ�շ�����

//����
#define NEWLAND_LORAWAN_NETWORK_ID          (uint32_t)(0x004E4C45) //"NLE"��ASCII��ֵ��OTAA����ʱʹ��
#define NEWLAND_LORAWAN_SKEY 				{ 'N', 'e', 'w', 'l', 'a', 'n', 'd', ' ', 'E', 'D', 'U', '2', '0', '1', '8', '2' }//�Ự��Կ��������������ÿ����ͬ����
#if (NEWLAND_USE_RX_TX_RF_SET != false)
#define NEWLAND_RECEIVE_DELAY1 (uint16_t)(3000)
#ifdef TYPE_CLASS_C
#define NEWLAND_RECEIVE_DELAY2 (uint16_t)(0)
#else
#define NEWLAND_RECEIVE_DELAY2 (uint16_t)(3000+NEWLAND_RECEIVE_DELAY1)
#endif /* TYPE_CLASS_C */
#endif /* (NEWLAND_USE_RX_TX_RF_SET != false) */

#endif //_USER_DEFINE_H_
