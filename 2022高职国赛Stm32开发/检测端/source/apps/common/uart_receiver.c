/* Includes ------------------------------------------------------------------*/
#include "uart_receiver.h"
#include "usart1-board.h"

void uartReceiver() {
    if(F_USART1_RX_RECEIVING)//���ڽ��մ�������
    {
        USART1_RX_TIMEOUT_COUNT++;//���ڳ�ʱ����
        if(USART1_RX_TIMEOUT_COUNT>USART1_RX_TIMEOUT)//���ݽ��ռ������3ms
        {   //���ڽ�����ɻ����
            F_USART1_RX_RECEIVING=false;
            USART1_RX_TIMEOUT_COUNT=0;
            F_USART1_RX_FINISH=true;
        }
    }
}
