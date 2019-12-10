//**************************************************************************************
/** \file task_EdgeSense.cpp
 *    This file contains source code for a sumo robot to detect the edge of the competition
 *    ring using IR sensors. The task interfaces with the other tasks in the software using
 *    FreeRTOS. */
//**************************************************************************************

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/wdt.h>                        // Watchdog timer header

#include "shared_data_sender.h"
#include "shared_data_receiver.h"
#include "task_EdgeSense.h"                      // Header for this file
#include "shares.h"
#include "IR_sensor.h"

//-------------------------------------------------------------------------------------
/** This constructor creates a new edge sensing task. Its main job is to call the
 *  parent class's constructor which does most of the work.
 *  @param a_name A character string which will be the name of this task
 *  @param a_priority The priority at which this task will initially run (default: 0)
 *  @param a_stack_size The size of this task's stack in bytes 
 *                      (default: configMINIMAL_STACK_SIZE)
 *  @param p_ser_dev Pointer to a serial device (port, radio, SD card, etc.) which can
 *                   be used by this task to communicate (default: NULL)
 */

task_EdgeSense::task_EdgeSense (const char* a_name, 
					  unsigned portBASE_TYPE a_priority, 
					  size_t a_stack_size,
					  emstream* p_ser_dev
					 )
	: frt_task (a_name, a_priority, a_stack_size, p_ser_dev)
{
	// Nothing is done in the body of this constructor. All the work is done in the
	// call to the frt_task constructor on the line just above this one
}


//-------------------------------------------------------------------------------------
/** This task reads the IR sensors attached to the sumo robot for the purpose of detecting
 *  the edge of the competition ring, a white line. If a sensor is triggered, the boolean
 *  share IR_flg is changed to true.
 */

void task_EdgeSense::run (void)
{
	// Make a variable which will hold times to use for precise task scheduling
	portTickType previousTicks = xTaskGetTickCount ();

	// Wait a little while for user interface task to finish up
	delay_ms(10);
	
	// Create IR_sensor objects for the IR sensors on the robot
	IR_sensor edgesensor1(&PORTF,6);
	IR_sensor edgesensor2(&PORTF,7);
	// IR_sensor edgesensor3(&PORTF,2);
	// IR_sensor edgesensor4(&PORTC,7);
	
	while(1)
	{
		// When the sensor is triggered, change IR_flg to be true. Otherwise IR_flg is false
		if(!edgesensor1.read() || !edgesensor2.read())  
		{
			IR_flg->put(true);
		}
		else
		{
			IR_flg->put(false);
		}
		
		runs++;
		delay_from_to_ms(previousTicks,10);
	}
}