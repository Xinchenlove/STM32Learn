#include "configs.h"
#include "flash.h"

uint8_t currentPage = MainPage;	
uint8_t sensorType = TemperatureDev;											
uint8_t channelNum = 0;

uint32_t rfFrequency=DEFAULT_RF_FREQUENCY; 			// Lora�����ŵ�

/**********************************************************************************************
*������void ReadFlashCfg()
*���ܣ���ȡLora�ڵ������
*���룺��
*�������
*����˵������
**********************************************************************************************/
void ReadFlashCfg() {
    uint8_t sensorType = STMFLASH_ReadWord(FLASH_SENSOR_TYPE_ADDR);
    setSensorType(sensorType);
    if (sensorType > 6)
        sensorType = 0;
    printf("����������=%d\n",sensorType);

    uint32_t rfFrequency = STMFLASH_ReadWord(FLASH_LG_FREQUENCY_ADDR);
    if(STMFLASH_ReadWord(FLASH_LG_FREQUENCY_ADDR) == 0)
        rfFrequency = DEFAULT_RF_FREQUENCY;

    setRfFrequency(rfFrequency);
    uint8_t channelNum = (rfFrequency - 400000000)/ 300000;
    setChannelNum(channelNum);
    if (channelNum > 200) {
        rfFrequency = 400000000;
        channelNum = 0;
    }
    printf("Ƶ��Ϊ%d Hz\n",rfFrequency);
}

uint8_t getSensorType(){
	return sensorType;
}

void setSensorType(uint8_t sensorTypeInput){
	 sensorType = sensorTypeInput;
}

uint8_t getCurrentPage(){
	return currentPage;
}

void setCurrentPage(uint8_t currentPageInput){
	currentPage = currentPageInput;
}

uint8_t getChannelNum(){
	return channelNum;
}

void setChannelNum(uint8_t channelNumInput){
	channelNum = channelNumInput;
}

void channelNumPP(){
	channelNum++;
}

void channelNumSS(){
	channelNum--;
}

uint32_t getRfFrequency() {
    return rfFrequency;
}

void setRfFrequency(uint32_t rf_frequencyInput) {
    rfFrequency = rf_frequencyInput;
}
