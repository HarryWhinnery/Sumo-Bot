//**************************************************************************************
/** \file IR_sensor.cpp
 *    This file contains source code for a IR sensor class that consists of a constructor
 *    to setup the microcontroller for the IR sensor and a function to read the pin.
 */
//**************************************************************************************


#include "IR_sensor.h"

//-------------------------------------------------------------------------------------
/** This constructor creates a new IR sensor object.
 *  @param p_port The port of the micro controller that the input pin is located on
 *  @param pin The number of the input pin
 */

IR_sensor::IR_sensor(PORT_t* p_port, uint8_t pin):gp_port(p_port),gpin_bm(1<<pin)
{
	// Initializes pin used for IR sensor to input
	gp_port->DIR &= ~(gpin_bm);
	
} //IR_sensor


//-------------------------------------------------------------------------------------
/** This method reads the output of the IR sensor.
 *  @return value A boolean that returns true if IR not triggered and false if IR triggered
 */

bool IR_sensor::read(void)
{
	// Reads the input of the pin setup in the constructor and returns a true/false statement
	bool value = gp_port->IN & gpin_bm;
	return value;
}


// default destructor
IR_sensor::~IR_sensor()
{
	
} //~IR_sensor
