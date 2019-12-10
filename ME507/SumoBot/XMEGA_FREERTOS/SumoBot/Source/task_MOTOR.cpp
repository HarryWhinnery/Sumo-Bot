//**************************************************************************************
/** \file task_MOTOR.cpp
 *    This file contains source code for a motor controller for a sumo robot.The task
 *    interfaces with the other tasks in the software using FreeRTOS. 
 */

//**************************************************************************************

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/wdt.h>                        // Watchdog timer header

#include "shared_data_sender.h"
#include "shared_data_receiver.h"
#include "task_MOTOR.h"                      // Header for this file
#include "Motor_Driver.h"
#include "shares.h"

//-------------------------------------------------------------------------------------
/** This constructor creates a new motor control task. Its main job is to call the
 *  parent class's constructor which does most of the work.
 *  @param a_name A character string which will be the name of this task
 *  @param a_priority The priority at which this task will initially run (default: 0)
 *  @param a_stack_size The size of this task's stack in bytes 
 *                      (default: configMINIMAL_STACK_SIZE)
 *  @param p_ser_dev Pointer to a serial device (port, radio, SD card, etc.) which can
 *                   be used by this task to communicate (default: NULL)
 */

task_MOTOR::task_MOTOR (const char* a_name, 
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
/** This task controls the motors based on the input from the various sensors on the
 *  sumo robot. The robot only uses the states for moving forward and turning in one direction
 *  due to issues with a motor driver failing.
 */

void task_MOTOR::run (void)
{
	// Make a variable which will hold times to use for precise task scheduling
	portTickType previousTicks = xTaskGetTickCount ();

	// Wait a little while for user interface task to finish up
	delay_ms(10);
	
	// Initializes the motors by creating motor_driver objects
	Motor_Driver motor1(&PORTD,3,2,4,5,&TCD0,&TCD0);
	Motor_Driver motor2(&PORTC,1,3,5,6,&TCC0,&TCC0);
	
	
	while(1)
	{
		switch (state)
		{
			// Sets the motion of sumo robot to forward
			case FORWARD:
			{
				motor1.set_duty_cycle(50);
				motor2.set_duty_cycle(50);
				// Transitions to turn if front IR sensors are activated
				if (IR_flg->get())
				{
					
					transition_to (TURN);
				}
				break;
			}
			// Sets the motion of sumo robot to backward
			case BACKWARD:
			{
				motor1.set_duty_cycle(-50);
				motor2.set_duty_cycle(-50);
				if (!IR_flg->get())
				{
					transition_to (TURN);
				}
				break;
			}
			// Sets the motion of sumo robot to stop
			case MOTOR_STOP:
			{
				motor1.set_duty_cycle(0);
				motor2.set_duty_cycle(0);
				transition_to(TURN);	
				break;
			}
			// Sets the motion of sumo robot to turn
			case TURN:
			{
				motor1.set_duty_cycle(50);
				motor2.set_duty_cycle(-50);
				// Transitions to foward if front IR sensors are disabled
				if (!IR_flg->get())
				{
					transition_to(FORWARD);
				}
				break;
			}
			// If theres an issue, disables the motors
			default:
			{
				motor1.set_duty_cycle(0);
				motor2.set_duty_cycle(0);
				break;
			}
		}
		runs++;
		delay_from_to_ms(previousTicks,10);
	}
}