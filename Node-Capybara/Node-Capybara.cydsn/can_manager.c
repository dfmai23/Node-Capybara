#include "can_manager.h"
#include "sd_manager.h"
#include "SoC_manager.h"

#define SENSOR_STATUS_ID	0x247
#define BMS_STATUS_ID 		0x188
#define BMS_CURRENT_ID		0x288
#define BMS_VOLTAGE_ID		0x388

DataPacket SENSOR_STATUS;   //0x247
DataPacket BMS_STATUS;		//0x188
DataPacket BMS_CURRENT;		//0x288
DataPacket BMS_VOLTAGE;		//0x388

CAN_1_TX_MSG SENS_STAT;		//0x247
CAN_1_DATA_BYTES_MSG sens_data;


CY_ISR(status_isr_custom) {
	SENSOR_STATUS.millicounter = millis_timer_ReadCounter();
	CAN_1_SendMsg(&SENS_STAT);
    //DataPacket * SENSOR_STATUS_ptr = &SENSOR_STATUS;
	//sd_buffer(LOGGER_HEARTBEAT_ptr);
}

void can_init() {
	CAN_1_GlobalIntEnable(); // CAN Initialization
	CAN_1_Init();
	CAN_1_Start();
	
	//initialize all the can messages 
	can_msg_init(&SENSOR_STATUS, SENSOR_STATUS_ID); 
	can_msg_init(&BMS_STATUS, BMS_STATUS_ID); 
	can_msg_init(&BMS_VOLTAGE, BMS_VOLTAGE_ID);
	
	status_timer_Start();
	status_isr_StartEx(status_isr_custom);
} // can_init()


//initalize CAN message variables with FF's everywhere
void can_msg_init(DataPacket* can_msg, uint16_t id) {
	uint8_t i;
	can_msg->id = id;
	can_msg->length = 8;
	can_msg->millicounter = 0;
	for(i=0; i<can_msg->length; i++) {
		can_msg->data[i] = 0xFF;
	}
	
	if(id == SENSOR_STATUS_ID) {		//set up sensor message to send to CAN bus
		SENS_STAT.id = SENSOR_STATUS_ID;
		SENS_STAT.rtr = 0;
		SENS_STAT.ide = 0;
		SENS_STAT.dlc = 0x08;
		SENS_STAT.irq = 1;
		SENS_STAT.msg = &sens_data;
		for(i=0; i<SENS_STAT.dlc; i++)
			sens_data.byte[i] = 0x00;   //sens_stat data
        sens_data.byte[7] = 0x01;       //heartbeat
	}
} //can_msg_init()

/*  recieves can message from bus can compares it with is respective id*/
void can_process(DataPacket* can_msg){
	int status = 0;		//returns 1 if message is updated
    switch (can_msg->id) {
    case BMS_CURRENT_ID:    //0x288
	case BMS_VOLTAGE_ID:	//0x388
		status = can_compare(&BMS_VOLTAGE, can_msg);
        if(status)
           SoC_volt_calc();
        break;
    default:
        break;
    } //switch
}

/*	compares received can message with the latest can message of the same id.
	if it is different, it will add update that DataPacket variable and add it to the can buffer	
	returns: 1 if message was updated, 0 if message same as before */
int can_compare(DataPacket* prev_msg, DataPacket* new_msg) {
	uint8_t i, j;
	uint8_t offset = 0;
	DataPacket temp;
 
	temp.id = new_msg->id;
	temp.length = new_msg->length;
	temp.millicounter = new_msg->millicounter;
	for(i=0; i<temp.length; i++) {
		temp.data[i] = new_msg->data[i];
	}
	
	//bytes received in little endian so have to reverse to big endian 32bits
	for(i=0; i<(new_msg->length/2); i++) {		//swap bytes 0-3
		new_msg->data[i+offset] = temp.data[offset + temp.length/2 - i - 1];
	}//for
	offset = 4;
	for(i=0; i<(new_msg->length/2); i++) {		//swap bytes 4-7
		new_msg->data[i+offset] = temp.data[offset + temp.length/2 - i - 1];
	}//for
	
	
	for(i=0; i<new_msg->length; i++) {					//compare all 8 data bytes
		if(prev_msg->data[i] != new_msg->data[i]) {		//update it if data[] has changed
			prev_msg->id = new_msg->id;
			prev_msg->length = new_msg->length;
			prev_msg->millicounter = new_msg->millicounter;	
			for(j=0; j<new_msg->length; j++) {
				prev_msg->data[j] = new_msg->data[j];
			}
			return 1;
		}//if
	}//for
	return 0;
}


void can_test_send() {
	uint8_t i;
	CAN_1_TX_MSG message;
	CAN_1_DATA_BYTES_MSG test_data;

	message.id = 0x100;
	message.rtr = 0;
	message.ide = 0;
	message.dlc = 0x08;
	message.irq = 1;
	message.msg = &test_data;

	for(i=0;i<8;i++)
		test_data.byte[i] = 2;

	CAN_1_SendMsg(&message);
} // can_test_send()


void can_test_receive() {
	DataPacket test_msg;
    uint8 i;
	
    //test packets
    for(i=100; i<115; i++) { 
		test_msg.millicounter = millis_timer_ReadCounter();    
		test_msg.id = 0x0923;
		test_msg.length = 8;
		test_msg.data[0]= 1;
		test_msg.data[1]= 2;
		test_msg.data[2]= 3;
		test_msg.data[3]= 4;
		test_msg.data[4]= 5;
		test_msg.data[5]= 6;
		test_msg.data[6]= 7;
        test_msg.data[7]= 8;
		
		can_process(&test_msg);
    } //for
}
