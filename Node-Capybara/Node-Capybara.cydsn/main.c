/* Node-Capybara
	 This node logs aux sensor data
 */

#include <project.h>
#include "data.h"
#include "can_manager.h"
#include "usb_manager.h"
#include "sd_manager.h"
#include "speed_manager.h"

int main(void) {
	CYGlobalIntEnable;      //Uncomment this line to enable global interrupts 

	uint8_t atomic_state = CyEnterCriticalSection(); // BEGIN ATOMIC
	can_init();
	sd_init();
	speed_init();
	//usb_init();
	//wdt_init();
	CyDelay(50);				//give some time to finish setup
	CyExitCriticalSection(atomic_state);               // END ATOMIC
	
	for(;;)	{
	    //can_test_send();
		//can_test_receive();
		//sd_writetest();
		CyDelay(1000);
	} // main loop

	return 0;
} // main()
