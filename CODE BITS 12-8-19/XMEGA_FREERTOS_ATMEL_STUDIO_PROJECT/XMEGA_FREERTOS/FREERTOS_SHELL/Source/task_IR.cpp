/*
 * task_IR.cpp
 *
 * Created: 11/5/2019 7:53:37 PM
 * Author : camka
 */ 

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/wdt.h>                        // Watchdog timer header

#include "shared_data_sender.h"
#include "shared_data_receiver.h"
#include "task_IR.h"
#include "IR_sensor.h"

//-------------------------------------------------------------------------------------
/** This constructor creates a new data acquisition task. Its main job is to call the
 *  parent class's constructor which does most of the work.
 *  @param a_name A character string which will be the name of this task
 *  @param a_priority The priority at which this task will initially run (default: 0)
 *  @param a_stack_size The size of this task's stack in bytes 
 *                      (default: configMINIMAL_STACK_SIZE)
 *  @param p_ser_dev Pointer to a serial device (port, radio, SD card, etc.) which can
 *                   be used by this task to communicate (default: NULL)
 */

task_IR::task_IR (const char* a_name, 
					  unsigned portBASE_TYPE a_priority, 
					  size_t a_stack_size,
					  emstream* p_ser_dev
					 )
	: frt_task (a_name, a_priority, a_stack_size, p_ser_dev)
{
	// Nothing is done in the body of this constructor. All the work is done in the
	// call to the frt_task constructor on the line just above this one
}


void task_IR::run (void)
{
    // Make a variable which will hold times to use for precise task scheduling
    portTickType previousTicks = xTaskGetTickCount ();

    // Wait a little while for user interface task to finish up
    delay_ms(10);
	
	/* Replace with your application code */
	PORTA.DIR |= (1<<4);		//Set PA4 to output (LED)

	IR_sensor test_IR_sensor (&PORTA, 5);
    
	while (1) 
    {
		
		if (test_IR_sensor.read())
		{
			PORTA.OUT = 0<<0;
		}
		else
		{
			PORTA.OUT = 1<<0;
		}
		
    }
}



