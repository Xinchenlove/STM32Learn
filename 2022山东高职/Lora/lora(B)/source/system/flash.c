#include "flash.h"
#include "stm32l1xx_hal_flash_ex.h"
#include "stm32l1xx_hal_flash.h"

/**********************************************************************************************
*������uint32_t STMFLASH_ReadWord(uint32_t faddr)
*���ܣ���ȡָ����ַ����(32λ����)
*���룺faddr:����ַ(�˵�ַ����Ϊ2�ı���!!)
*�������Ӧ����
*����˵������
**********************************************************************************************/
uint32_t STMFLASH_ReadWord(uint32_t faddr)
{
    return *(__IO uint32_t*)faddr;
}

/**********************************************************************************************
*������void STMFLASH_Write(uint32_t WriteAddr,uint32_t *pBuffer,uint32_t NumToWrite)
*���ܣ���ȡEEPROM����д�����
*���룺WriteAddr:��ʼ��ַ
			 pBuffer:����ָ��
			 NumToWrite:��(32λ)��
*�������
*����˵������
**********************************************************************************************/
void STMFLASH_Write(uint32_t WriteAddr,uint32_t *pBuffer,uint32_t NumToWrite)
{
    HAL_FLASH_Unlock();//��סFLASH
    HAL_FLASHEx_DATAEEPROM_Unlock(); //����FLASH
    //����FLASH
    FLASH_EraseInitTypeDef FLASH_EraseTypeDef;//��ʼ��FLASH_EraseInitTypeDef
    FLASH_EraseTypeDef.TypeErase = FLASH_TYPEERASE_PAGES;
    FLASH_EraseTypeDef.PageAddress = WriteAddr;
    FLASH_EraseTypeDef.NbPages = 1;
    uint32_t PageError = 0;//����PageError
    HAL_FLASHEx_Erase(&FLASH_EraseTypeDef, &PageError);//���ò�������
    uint32_t i;
    for(i=0; i<NumToWrite; i++)
    {
        HAL_FLASHEx_DATAEEPROM_Program(TYPEPROGRAM_WORD, WriteAddr, pBuffer[i]);//FLASH_ProgramHalfWord(WriteAddr,pBuffer[i]);
        WriteAddr+=4;//��ַ����4.
    }
    HAL_FLASHEx_DATAEEPROM_Lock();//��סFLASH
    HAL_FLASH_Lock();//��סFLASH
}

/**********************************************************************************************
*������void WriteFlashTest(uint32_t Addr,uint32_t WriteFlashData)
*���ܣ���ȡEEPROM����д�����
*���룺WriteAddr:��ʼ��ַ
			 WriteFlashData:����
*�������
*����˵������
**********************************************************************************************/
void WriteFlashTest(uint32_t Addr,uint32_t WriteFlashData)
{
    HAL_FLASH_Unlock();//��סFLASH
    HAL_FLASHEx_DATAEEPROM_Unlock();//����FLASH
    //����FLASH
    FLASH_EraseInitTypeDef FLASH_EraseTypeDef;//��ʼ��FLASH_EraseInitTypeDef
    FLASH_EraseTypeDef.TypeErase = FLASH_TYPEERASE_PAGES;
    FLASH_EraseTypeDef.PageAddress = Addr;
    FLASH_EraseTypeDef.NbPages = 1;
    uint32_t PageError = 0;//����PageError
    HAL_FLASHEx_Erase(&FLASH_EraseTypeDef, &PageError);//���ò�������
    HAL_FLASHEx_DATAEEPROM_Program(TYPEPROGRAM_WORD, Addr, WriteFlashData);//��FLASH��д
    HAL_FLASHEx_DATAEEPROM_Lock();//��סFLASH
    HAL_FLASH_Lock();//��סFLASH
}

//��ָ����ַ��ʼ����ָ�����ȵ�����
//ReadAddr:��ʼ��ַ
//pBuffer:����ָ��
//NumToWrite:��(32λ)��
void STMFLASH_Read(uint32_t ReadAddr,uint32_t *PBuffer,uint32_t NumToRead)
{
    uint32_t i;
    for(i=0; i<NumToRead; i++)
    {
        PBuffer[i]=STMFLASH_ReadWord(ReadAddr);//��ȡ4���ֽ�.
        ReadAddr+=4;//ƫ��4���ֽ�.
    }
}

/**********************************************************************************************
*������uint32_t PrintFlashTest(uint32_t FLASH_ADDR)
*���ܣ���ȡָ����ַ����(32λ����)
*���룺faddr:����ַ(�˵�ַ����Ϊ2�ı���!!)
*�������Ӧ����
*����˵������
**********************************************************************************************/
uint32_t PrintFlashTest(uint32_t FLASH_ADDR)
{
    uint32_t temp = *(__IO uint32_t*)(FLASH_ADDR);
	
    return temp;
}


