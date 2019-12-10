//**************************************************************************************
/** \file task_MOTOR.h
 *    This file contains header stuff for the motor control task.
 */
//**************************************************************************************

// This define prevents this .h file from being included multiple times in a .cpp file
#ifndef _TASK_MOTOR_H_
#define _TASK_MOTOR_H_

#include <stdlib.h>                         // Prototype declarations for I/O functions

#include "FreeRTOS.h"                       // Primary header for FreeRTOS
#include "task.h"                           // Header for FreeRTOS task functions
#include "queue.h"                          // FreeRTOS inter-task communication queues

#include "rs232int.h"                       // ME405/507 library for serial comm.
#include "time_stamp.h"                     // Class to implement a microsecond timer
#include "frt_task.h"                       // Header for ME405/507 base task class
#include "frt_queue.h"                      // Header of wrapper for FreeRTOS queues
#include "frt_text_queue.h"                 // Header for a "<<" queue class
#include "frt_shared_data.h"                // Header for thread-safe shared data

#include "shares.h"                         // Global ('extern') queue declarations



//-------------------------------------------------------------------------------------
/** This task controls the motors based on the input from the various sensors on the
 *  sumo robot. The robot only uses the states for moving forward and turning in one direction
 *  due to issues with a motor driver failing.
 */

class task_MOTOR : public frt_task
{
private:
	// No private variables or methods for this class

protected:
	enum MOTOR_states {
		FORWARD,
		MOTOR_STOP,
		BACKWARD,
		TURN
	};					//!< Task state
	uint8_t ctr;		//!< Loop counter

public:
	// This constructor creates a motor task object
	task_MOTOR (const char*, unsigned portBASE_TYPE, size_t, emstream*);

	/** This method is called by the RTOS once to run the task loop for ever and ever.
	 */
	void run (void);
};

#endif // _TASK_MOTOR_H_
