//**************************************************************************************
/** \file IR_sensor.h
 *    This file contains header stuff for a IR sensor class that consists of a constructor
 *    to setup the micro controller for the IR sensor and a function to read the pin.
 */
//**************************************************************************************


#ifndef __IR_SENSOR_H__
#define __IR_SENSOR_H__
#include <avr/io.h>
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
/** This file contains code for a IR sensor class that consists of a constructor
 *  to setup the micro controller for the IR sensor and a function to read the pin.
 */


class IR_sensor
{
//variables
public:
protected:
	PORT_t* gp_port;
	uint8_t gpin_bm;
private:

//functions
public:
	// This constructor creates a IR sensor object
	IR_sensor(PORT_t* p_port, uint8_t pin);
	// This method returns the output of the IR sensor as boolean
	bool read(void);
	// Destructor
	~IR_sensor();
protected:
private:

}; //IR_sensor

#endif //__IR_SENSOR_H__
