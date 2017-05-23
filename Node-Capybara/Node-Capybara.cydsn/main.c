/* Node-Beaver
	 This node logs data via CAN and presents the data to the outside world.
 */

#include <project.h>
#include "data.h"
#include "can_manager.h"
#include "usb_manager.h"
#include "sd_manager.h"


int main(void) {
	CYGlobalIntEnable;      //Uncomment this line to enable global interrupts 

	uint8_t atomic_state = CyEnterCriticalSection(); // BEGIN ATOMIC
	can_init();
	sd_init();
	//usb_init();
	//wdt_init();
	CyDelay(500);				//give some time to finish setup
	CyExitCriticalSection(atomic_state);               // END ATOMIC
	
	for(;;)	{
	    //can_test_send();
		//can_test_receive();
		sd_writetest();
		CyDelay(1000);
	} // main loop

	return 0;
} // main()

/* when a can message is recieved will immediately save messages to external devices
	- transmit over xbee
	- write to sd
	- write to usb	*/
void msg_recieve(DataPacket * msg) {
	if(can_process(msg)) {	//if message is new data value
		//sd_buffer(msg);
		//usb_write(msg);
	}
}
