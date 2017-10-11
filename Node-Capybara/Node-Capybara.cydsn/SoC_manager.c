
#include "SoC_manager.h"

extern volatile DataPacket BMS_CURRENT;
extern volatile DataPacket BMS_VOLTAGE;

extern CAN_1_TX_MSG SENS_STAT;		//0x247
extern CAN_1_DATA_BYTES_MSG sens_data;

double SoC_map_pct[] = {50, 35, 25, 15, 10};
double SoC_map[] = {100.8, 99.4, 98.0, 96.6, 95.2};

void SoC_init() {
	millis_timer_Start();	
}

//voltage SoC
void SoC_volt_calc() {
	
	//voltage = 0x0001C3E3;
	//sprintf(volt_string, "%03d.%01dV", voltage/1000, voltage/100%10);
    
	uint32_t byte4 = BMS_VOLTAGE.data[7] << 24;
	uint32_t byte3 = BMS_VOLTAGE.data[6] << 16;
	uint32_t byte2 = BMS_VOLTAGE.data[5] << 8;
	uint32_t byte1 = BMS_VOLTAGE.data[4];
	uint32_t voltage_hex = byte4 | byte3 | byte2 | byte1;
    double voltage = ((double)voltage_hex) / 1000;
    int SoC_pct;
    
    if (voltage > SoC_map[0]) //>50%
        SoC_pct = 100;
    else if (voltage <= SoC_map[0] && voltage > SoC_map[1])
        SoC_pct = 50;
    else if (voltage <= SoC_map[1] && voltage > SoC_map[2])
        SoC_pct = 35;
    else if (voltage <= SoC_map[2] && voltage > SoC_map[3])
        SoC_pct = 25;
    else if (voltage <= SoC_map[2] && voltage > SoC_map[3])
        SoC_pct = 15;
    else //voltage < SoC_map[4]
        SoC_pct = 10;
    
    sens_data.byte[6] = SoC_pct;
}