//**************************************************************************************
/** \file task_EdgeSense.h
 *    This file contains header stuff for the edge sensing task.
 */
//**************************************************************************************

// This define prevents this .h file from being included multiple times in a .cpp file
#ifndef _TASK_EdgeSense_H_
#define _TASK_EdgeSense_H_

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
/** This task reads the IR sensors attached to the sumo robot for the purpose of detecting
 *  the edge of the competition ring, a white line. If a sensor is triggered, the boolean
 *  share IR_flg is changed to true.
 */

class task_EdgeSense : public frt_task
{
private:
	// No private variables or methods for this class

protected:


public:
	// This constructor creates a edge sensing task object
	task_EdgeSense (const char*, unsigned portBASE_TYPE, size_t, emstream*);

	/** This method is called by the RTOS once to run the task loop for ever and ever.
	 */
	void run (void);
};

#endif // _TASK_EdgeSense_H_
