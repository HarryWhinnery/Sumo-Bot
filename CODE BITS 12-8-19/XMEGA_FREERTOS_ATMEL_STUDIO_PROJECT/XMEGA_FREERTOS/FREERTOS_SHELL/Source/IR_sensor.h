/* 
* IR_sensor.h
*
* Created: 11/5/2019 7:55:20 PM
* Author: camka
*/


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

#include "math.h"

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
	IR_sensor(PORT_t* p_port, uint8_t pin);
	bool read(void);
	~IR_sensor();
protected:
	
private:
	IR_sensor( const IR_sensor &c );
	IR_sensor& operator=( const IR_sensor &c );

}; //IR_sensor

#endif //__IR_SENSOR_H__
