/* Includes ------------------------------------------------------------------*/
#include "NS_Radio.h"
#include <string.h>
#include "board.h"
#include "radio.h"

static uint16_t LoRaBufferSize = BUFFER_SIZE;
static uint8_t LoRaBuffer[BUFFER_SIZE];
static int8_t RssiValue = 0;
static int8_t SnrValue = 0;

static RadioEvents_t RadioEvents;

/**********************************************************************************************
*������void NS_RadioEventsInit( void )
*���ܣ�����Ƶģ���¼��ص��������г�ʼ��
*���룺��
*�������
*����˵������
**********************************************************************************************/
void NS_RadioEventsInit( void )
{
    // Radio initialization
    RadioEvents.TxDone = OnTxDone;
    RadioEvents.RxDone = OnRxDone;
    RadioEvents.TxTimeout = OnTxTimeout;
    RadioEvents.RxTimeout = OnRxTimeout;
    RadioEvents.RxError = OnRxError;

    Radio.Init( &RadioEvents );
}


/**********************************************************************************************
*������void NS_RadioInit( uint32_t freq, int8_t power, uint32_t txTimeout )
*���ܣ�����Ƶģ�鷢�͡����ղ������г�ʼ��
*���룺
*			freq�ز�Ƶ�ʣ�����433MHz����Ƶ�����
*			power���书�ʣ����20
*			txTimeout���ͳ�ʱʱ��
*�������
*����˵������
**********************************************************************************************/
void NS_RadioSetTxRxConfig( uint32_t freq, int8_t power, uint32_t txTimeout )
{
    Radio.SetChannel( freq );
    Radio.SetTxConfig( MODEM_LORA, power, 0, LORA_BANDWIDTH,
                       LORA_SPREADING_FACTOR, LORA_CODINGRATE,
                       LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                       true, 0, 0, LORA_IQ_INVERSION_ON, txTimeout);
    Radio.SetRxConfig( MODEM_LORA, LORA_BANDWIDTH, LORA_SPREADING_FACTOR,
                       LORA_CODINGRATE, 0, LORA_PREAMBLE_LENGTH,
                       LORA_SYMBOL_TIMEOUT, LORA_FIX_LENGTH_PAYLOAD_ON,
                       0, true, 0, 0, LORA_IQ_INVERSION_ON, true );
}

/**********************************************************************************************
*������void NS_RadioInit( uint32_t freq, int8_t power, uint32_t txTimeout, uint32_t rxTimeout)
*���ܣ�����Ƶģ�鷢�͡����ղ������г�ʼ��
*���룺
*			freq�ز�Ƶ�ʣ�����433MHz����Ƶ�����
*			power���书�ʣ����20
*			txTimeout���ͳ�ʱʱ��
*			uint32_t rxTimeout ���ճ�ʱʱ��
*�������
*����˵������
**********************************************************************************************/
void NS_RadioInit( uint32_t freq, int8_t power, uint32_t txTimeout, uint32_t rxTimeout)
{
	 NS_RadioEventsInit();//������Ƶģ��ע���¼��ص�����
     NS_RadioSetTxRxConfig( freq, power, txTimeout );
	 Radio.Rx( rxTimeout );//����LoRaģ��Ϊ����ģʽ��ͬʱ���ó�ʱʱ�䣬������
}

/**********************************************************************************************
*������uint16_t ReadRadioRxBuffer( uint8_t *payload)
*���ܣ���ȡ��Ƶ���ջ�����Ϣ��������ȡ���յ������ݳ��Ⱥͻ������ݡ�
*���룺��
*�����uint8_t *payload, ָ�룬ָ��Ҫ���ڴ�Ž��ջ���ĵ�ַ
*���أ����ؽ��յ������ݳ���
*����˵����ÿ����һ��ReadRadioRxBuffer( )������LoRaBufferSize�ᱻ��0.
**********************************************************************************************/
uint16_t ReadRadioRxBuffer( uint8_t *payload)
{
	  uint16_t LengthTemp;
	  LengthTemp = LoRaBufferSize;
	  if(LengthTemp <= 0)
	  {
        return 0;
	  }
	  LoRaBufferSize = 0;
    //payload = LoRaBuffer;
	  memcpy( payload, LoRaBuffer, LengthTemp );
	  return LengthTemp;
}

/**********************************************************************************************
*������void ReadRadioRssiSnr( int16_t *rssi, int8_t *snr )
*���ܣ���ȡ��Ƶ�ź�ǿ�Ⱥ������
*���룺��
*�����int16_t *rssi,�ź�ǿ�� int8_t *snr�����
*���أ���
*����˵������
**********************************************************************************************/
void ReadRadioRssiSnr( int16_t *rssi, int8_t *snr )
{
    *rssi = RssiValue;
    *snr = SnrValue;
}

void OnTxDone( void )
{
    Radio.Sleep( );
    Radio.Rx( RX_TIMEOUT_VALUE );
}

void OnRxDone( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr )
{
    Radio.Sleep( );
    LoRaBufferSize = size;
    memcpy( LoRaBuffer, payload, LoRaBufferSize );
    RssiValue = rssi;
    SnrValue = snr;
    Radio.Rx( RX_TIMEOUT_VALUE );
}

void OnTxTimeout( void )
{
    Radio.Sleep( );
	Radio.Rx( RX_TIMEOUT_VALUE );
}

void OnRxTimeout( void )
{
    Radio.Sleep( );
	Radio.Rx( RX_TIMEOUT_VALUE );
}

void OnRxError( void )
{
    Radio.Sleep( );
	Radio.Rx( RX_TIMEOUT_VALUE );
}
