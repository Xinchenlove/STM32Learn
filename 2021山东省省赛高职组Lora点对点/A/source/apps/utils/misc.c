/* Includes ------------------------------------------------------------------*/
#include "misc.h"

/*******************************************************************
*������uint8_t CHK(uint8_t *buf, uint8_t len)
*���ܣ������ۼӺ�
*���룺uint8_t *buf ����Ҫ�ۼӵ���
			 uint8_t len ���ۼ����ĸ���
*���أ��ۼӺ�
*����˵����
*******************************************************************/
uint8_t CHK(uint8_t *buf, uint8_t len) //У����
{
    uint8_t  RX_CHX=0;

    while(len--)
    {
        RX_CHX+= *buf;
        buf++;
    }

    return RX_CHX&=0xff;
}

uint32_t getCRC(uint8_t *buf, uint8_t len) {
    uint32_t crc = 0x0000ffff;
    for (int i = 0; i < len; i++) {
        crc ^= ((int) buf[i] & 0x000000ff);
        for (int j = 0; j < 8; j++) {
            if ((crc & 0x00000001) != 0) {
                crc >>= 1;
                crc ^= 0x0000a001;
            } else {
                crc >>= 1;
            }
        }
    }
		
    //�ߵ�λ���������������ع��߶�Modbus CRC16������
    return ((crc & 0xff00) >> 8) | ((crc & 0x00ff) << 8);
}

/*******************************************************************
*������void Uint16ToByteArray_BigEnd(uint16_t value, uint8_t *ret)
*���ܣ�byte����תuint32����
*���룺uint8_t *buf �����ֽ�byte����
*���أ�uint16_t����
*����˵����
*******************************************************************/
void Uint16ToByteArray_BigEnd(uint16_t value, uint8_t *ret)
{
    ret[0]=(value)>>8;
    ret[1]=(value)&0x00ff;
}

/*******************************************************************
*������uint16_t ByteArray2Uint16_BigEnd(uint8_t *buf)
*���ܣ�byte����תuint32����
*���룺uint8_t *buf �����ֽ�byte����
*���أ�uint16_t����
*����˵����
*******************************************************************/
uint16_t ByteArray2Uint16_BigEnd(uint8_t *buf)
{
    uint32_t ret=0;

    ret=(0x00ff&buf[0])<<8;
    ret|=(0x00ff&buf[1]);

    return ret;
}

/*******************************************************************
*������uint32_t ByteArray2Uint32_BigEnd(uint8_t *buf)
*���ܣ�byte����תuint32����
*���룺uint8_t *buf �����ֽ�byte����
*���أ�uint32_t����
*����˵����
*******************************************************************/
uint32_t ByteArray2Uint32_BigEnd(uint8_t *buf)
{
    uint32_t ret=0;

    ret=(0x00ff&buf[0])<<24;
    ret|=(0x00ff&buf[1])<<16;
    ret|=(0x00ff&buf[2])<<8;
    ret|=(0x00ff&buf[3]);

    return ret;
}











