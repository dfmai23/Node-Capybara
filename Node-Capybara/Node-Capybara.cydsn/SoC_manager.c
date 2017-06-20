
#include "SoC_manager.h"

extern DataPacket BMS_CURRENT;
extern DataPacket BMS_VOLTAGE;

extern CAN_1_TX_MSG SENS_STAT;		//0x247
extern CAN_1_DATA_BYTES_MSG data;

void SoC_init() {
	millis_timer_Start();	
}

//voltage SoC
void SoC_volt_calc() {
	uint32_t voltage_hex;
	uint32_t byte4 = BMS_VOLTAGE.data[7] << 24;
	uint32_t byte3 = BMS_VOLTAGE.data[6] << 16;
	uint32_t byte2 = BMS_VOLTAGE.data[5] << 8;
	uint32_t byte1 = BMS_VOLTAGE.data[4];
	voltage_hex = byte4 | byte3 | byte2 | byte1;
	
	//voltage = 0x0001C3E3;
	//sprintf(volt_string, "%03d.%01dV", voltage/1000, voltage/100%10);
    
    long voltage = (voltage_hex/1000);
    int SoC_pct;
}