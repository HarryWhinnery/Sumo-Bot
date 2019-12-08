/* 
* IR_sensor.cpp
*
* Created: 11/5/2019 7:55:20 PM
* Author: camka
*/


#include "IR_sensor.h"

// default constructor
IR_sensor::IR_sensor(PORT_t* p_port, uint8_t pin):gp_port(p_port),gpin_bm(1<<pin)
{
	gp_port->DIR &= ~(gpin_bm);
	
} //IR_sensor


//Read output of IR sensor
bool IR_sensor::read(void)
{
	bool value = gp_port->IN & gpin_bm;
	return value;
}


// default destructor
IR_sensor::~IR_sensor()
{
	
} //~IR_sensor
