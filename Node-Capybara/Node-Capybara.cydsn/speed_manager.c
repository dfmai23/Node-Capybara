/*
Reciprocal Counter based frequency measurement of tachometer sensor
resolution = 1/sysclk  (hz) = 1 us currently
highest freq = sysclk/2 = 500000Hz currently
lowest freq = 1/period = 0.2 Hz currently

pulselen = [period - count] / timerclk
freq = 1/[2pulselen]

    1 - front left
    2 - front right //currently no hardware
    3 - rear left
    4 - rear right
*/

#include "speed_manager.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

extern CAN_1_TX_MSG SENS_STAT;		//0x247
extern CAN_1_DATA_BYTES_MSG sens_data;

char Serial_Command;
char StringToPrint[90];
volatile uint32 Channel_1_Count, Channel_2_Count, Channel_3_Count, Channel_4_Count;
static int intFlag = 0;
static int intFlag2 = 0;
static int intFlag3 = 0;
static int intFlag4 = 0;
float32 Tacho_freq;
float32 pulselen;
float32 Tacho_freq2;
float32 pulselen2;
float32 Tacho_freq3;
float32 pulselen3;
float32 Tacho_freq4;
float32 pulselen4;
float32 voltage;

CY_ISR(Channel1_isr_Handler){
    Channel_1_Count = Channel_1_Timer_ReadCounter();
    intFlag = Channel_1_Timer_ReadStatusRegister();  
    CR1_Write(1);
      
    if(intFlag & Channel_1_Timer_STATUS_TC)
        Channel_1_Count = 0;
}
/*
CY_ISR(Channel2_isr_Handler){
    Channel_2_Count = Channel_2_Timer_ReadCounter();
    intFlag2 = Channel_2_Timer_ReadStatusRegister();  
    CR2_Write(1);
      
    if(intFlag2 & Channel_2_Timer_STATUS_TC)
        Channel_2_Count = 0;
}
*/
CY_ISR(Channel3_isr_Handler){
    Channel_3_Count = Channel_3_Timer_ReadCounter();
    intFlag3 = Channel_3_Timer_ReadStatusRegister();  
    CR3_Write(1);
      
    if(intFlag3 & Channel_3_Timer_STATUS_TC)
        Channel_3_Count = 0;
}
CY_ISR(Channel4_isr_Handler){
    Channel_4_Count = Channel_4_Timer_ReadCounter();
    intFlag4 = Channel_4_Timer_ReadStatusRegister();  
    CR4_Write(1);
      
    if(intFlag4 & Channel_4_Timer_STATUS_TC)
        Channel_4_Count = 0; 
}
void speed_init() {
    Channel_1_isr_StartEx(Channel1_isr_Handler); 
    Channel_1_Timer_Start();
    DVDAC_1_Start();
    Comp_1_Start();
    //My_ADC_1_Start();
    PGA_1_Start();
    /*
    Channel_2_isr_StartEx(Channel2_isr_Handler); 
    Channel_2_Timer_Start();
    DVDAC_2_Start();
    Comp_2_Start();
    PGA_2_Start();
    */
    Channel_3_isr_StartEx(Channel3_isr_Handler); 
    Channel_3_Timer_Start();
    DVDAC_3_Start();
    Comp_3_Start();
    PGA_3_Start();
	
	Channel_4_isr_StartEx(Channel4_isr_Handler); 
    Channel_4_Timer_Start();
    DVDAC_4_Start();
    Comp_4_Start();
    PGA_4_Start();
	
	//TestPWM_Start();
}

void speed_sense() {
    /*debugging
	if(UART_1_ReadRxStatus() == UART_1_RX_STS_FIFO_NOTEMPTY){
        Serial_Command=UART_1_GetChar();
    }
    //UART_1_ClearTxBuffer();
    //UART_1_ClearTxBuffer();
    My_ADC_StartConvert();
    voltage = My_ADC_CountsTo_Volts(My_ADC_GetResult32());
	*/
	
   	if(Channel_1_Count >= threshold){
        Tacho_freq = 0;
    }
    else {
    	pulselen = (Ch1Period - Channel_1_Count)/((float) timerCLK);
    	Tacho_freq = (1/(2*pulselen))/numSpokes1;
    }
    /*
    if(Channel_2_Count >= threshold) {
        Tacho_freq2 = 0;
    }
    else {
   		pulselen2 = (Ch2Period - Channel_2_Count)/((float) timerCLK);
    	Tacho_freq2 = (1/(2*pulselen2))/numSpokes2;
    }
    */
    if(Channel_3_Count >= threshold) {
        Tacho_freq3 = 0;
    }
    else {
	    pulselen3 = (Ch3Period - Channel_3_Count)/((float) timerCLK);
	    Tacho_freq3 = (1/(2*pulselen3))/numSpokes3;
    }
    
	if(Channel_4_Count >= threshold) {
        Tacho_freq4 = 0;
    }
    else {
	    pulselen4 = (Ch4Period - Channel_4_Count)/((float) timerCLK);
	    Tacho_freq4 = (1/(2*pulselen4))/numSpokes4;
    }
    
	//sprintf(StringToPrint," %lf  %lf %d \r\n",Tacho_freq,voltage,comparator_out_Read());
	//sprintf(StringToPrint," %lf  %lf %lf \r\n",Tacho_freq,Tacho_freq2,Tacho_freq3);
	//UART_1_PutString(StringToPrint);
	CyDelay(2);  
}