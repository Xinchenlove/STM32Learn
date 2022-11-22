/* Includes ------------------------------------------------------------------*/

#ifndef __MISC_H
#define __MISC_H

#include "stm32l1xx_hal.h"
#include "board.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************
*������uint8_t CHK(uint8_t *buf, uint8_t len)
*���ܣ������ۼӺ�
*���룺uint8_t *buf ����Ҫ�ۼӵ���
			 uint8_t len ���ۼ����ĸ���
*���أ��ۼӺ�
*����˵����
*******************************************************************/
uint8_t CHK(uint8_t *buf, uint8_t len);
	
uint32_t getCRC(uint8_t *buf, uint8_t len);

/*******************************************************************
*������uint16_t ByteArray2Uint16_BigEnd(uint8_t *buf)
*���ܣ�byte����תuint32����
*���룺uint8_t *buf �����ֽ�byte����
*���أ�uint16_t����
*����˵����
*******************************************************************/
uint16_t ByteArray2Uint16_BigEnd(uint8_t *buf);

/*******************************************************************
*������uint32_t ByteArray2Uint32_BigEnd(uint8_t *buf)
*���ܣ�byte����תuint32����
*���룺uint8_t *buf �����ֽ�byte����
*���أ�uint32_t����
*����˵����
*******************************************************************/
uint32_t ByteArray2Uint32_BigEnd(uint8_t *buf);

#ifdef __cplusplus
}
#endif

#endif /* __MISC_H */


