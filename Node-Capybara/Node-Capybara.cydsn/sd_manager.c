#include "sd_manager.h"


FS_FILE* pfile;
uint8_t sd_ok = 0;

const char set_time_file[] = "\\set_time.txt";
const char format_file[] = "\\format.txt";

DataPacket sd_queue[SD_QUEUE_LENGTH];
uint16_t sd_head = 0, sd_tail = 0;

	
CY_ISR(power_interrupt) {
	sd_stop();
	power_isr_ClearPending();
    CyDelay(3000);
    //CySoftwareReset();
    for(;;);	// halt program until IC shuts down
} // CY_ISR(power_interrupt)

//triggers every second
CY_ISR(sd_interrupt) {
	sd_write();
}

/* sd_init()
	Takes Time struct (time). Returns nothing.

	Initializes SD card filesystem.
	The following events will cause the sd_ok flag to be reset, which aborts all
	SD functions:
		- the SD card is not found
		- unable to create the "LOGS" directory
		- unable to create a directory named after the date
		- unable to create and open file for writing

	sd_ok is set when the SD card is functional */
void sd_init() {
	/* power_isr note:
		Triggers unexpectedly due to floating pin/environmental voltages and
		capacitance. power isr is disabled for prototyping only.	*/
	power_comp_Start();
	power_isr_ClearPending();
	power_isr_StartEx(power_interrupt);
	sd_timer_Start();
	sd_isr_StartEx(sd_interrupt);
    
	FS_Init();
    FS_FAT_SupportLFN();            //enable long file name: filenames>8bytes
	sd_ok = 1;
	char file_str[64], test_folder[32];

	if(FS_GetNumVolumes() == 1) {
		FS_SetFileWriteMode(FS_WRITEMODE_FAST);
		if((pfile = FS_FOpen(format_file, "r")))
			FS_FormatSD("");
		
        //create logs folder
		if(FS_ATTR_DIRECTORY != FS_GetFileAttributes("test_folder")) { // if not a dir
			if(FS_MkDir("test_folder")) {
				sd_ok = 0;
				return;
			} // if logs folder can't be created
        }
        
        // create log file
		sprintf(file_str, "\\test_folder\\test_file.txt");
		pfile = FS_FOpen(file_str, "w"); //create and open new file for writing
		if(pfile == NULL) {
			sd_ok = 0;
			return;
		} // if file does not exist

		// Set file time here
		//FS_FILETIME file_time;
		//unsigned long file_timestamp;
		/*
		file_time.Year = time.year;
		file_time.Month = time.month;
		file_time.Day = time.day;
		file_time.Hour = time.hour;
		file_time.Minute = time.minute;
		file_time.Second = time.second;
		*/
		//FS_FileTimeToTimeStamp(&file_time, &file_timestamp);
		//FS_SetFileTime(file_str, file_timestamp);
		/*FS_SetFileTimeEx(file_str, file_timestamp, FS_FILETIME_CREATE);	//doesnt work
		FS_SetFileTimeEx(file_str, file_timestamp, FS_FILETIME_ACCESS);
		FS_SetFileTimeEx(file_str, file_timestamp, FS_FILETIME_MODIFY);*/
	} // if a single file volume exists
    FS_Sync("");
} // sd_init()





/* sd_write()
	Writes current to the SD card. 
	Synchronizes the filesystem after it is  written. */
void sd_write() {
	if(!sd_ok) return;

	char buffer[64];
	short length = 0;
	
    uint8_t atomic_state = CyEnterCriticalSection(); // BEGIN ATOMIC
	for(sd_head=0; sd_head<sd_tail; sd_head++) {
		length = sprintf(buffer, "%X,%u,%X,%X,%X,%X,%X,%X,%X,%X\n",
			(unsigned)sd_queue[sd_head].id,
			MILLI_PERIOD - (unsigned)sd_queue[sd_head].millicounter,
			(unsigned)sd_queue[sd_head].data[0],
			(unsigned)sd_queue[sd_head].data[1],
			(unsigned)sd_queue[sd_head].data[2],
			(unsigned)sd_queue[sd_head].data[3],
			(unsigned)sd_queue[sd_head].data[4],
			(unsigned)sd_queue[sd_head].data[5],
			(unsigned)sd_queue[sd_head].data[6],
			(unsigned)sd_queue[sd_head].data[7]);

		FS_Write(pfile, buffer, length); // write to SD
	}
	FS_Sync(""); // sync to SD
	sd_head=0; sd_tail=0;
    CyExitCriticalSection(atomic_state);               // END ATOMIC
} // sd_write()


void sd_read() {
	if((pfile = FS_FOpen("\\BMS\\SoC.txt", "r"))) {	//open file for reading
		char buffer[64];
		//Time time;
		//DataPacket msg;
		FS_Read(pfile, buffer, 64); // read entire file
		FS_FClose(pfile);
	}
}


void sd_buffer(DataPacket * msg) {
	sd_queue[sd_tail] = *msg;
	sd_tail = ((sd_tail == SD_QUEUE_LENGTH-1) ? sd_tail:sd_tail++);	//if buffer full stay at tail
}
/* sd_stop()
	Takes and returns nothing.
	Closes the file, synchronizes, and unmounts SD card to prevent corruption.
*/
void sd_stop(void) {
	sd_write();
	FS_FClose(pfile);
	FS_Sync("");
	FS_Unmount("");
} // sd_stop()


void sd_writetest() {
	// test data writing
	char buffer[128];
	short length = 0;

	// test write
	FS_Write(pfile, "Type,Time,Value,ID\n", 19);
	length = sprintf(buffer, "%u,%X,%X,%u\n",
		1,0xFFFF, 0xFFFFFFFF, 224);
	FS_Write(pfile, buffer, length);

	sd_stop(); // for testing
	sd_ok = 0; // for testing
}//test_push
