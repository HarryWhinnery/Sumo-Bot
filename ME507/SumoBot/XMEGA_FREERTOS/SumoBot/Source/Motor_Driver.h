//**************************************************************************************
/** \file Motor_Driver.h
 *    This file contains header stuff for the motor driver class.
 */
//**************************************************************************************


#ifndef __MOTOR_DRIVER_H__
#define __MOTOR_DRIVER_H__
#include <avr/io.h>

//-------------------------------------------------------------------------------------
/** This file contains code for a motor driver class for a board using two
 *  half bridge motor drivers. The motor's speed can be controlled through the
 *  set_duty_cycle function.
 */

class Motor_Driver
{
	//variables
	public:
	protected:
		uint8_t pin1;			
		uint8_t pin2;			
		PORT_t* gp_port;		
		uint8_t gpinA_bm;
		uint8_t gpinB_bm;
		uint8_t gpinhA_bm;
		uint8_t gpinhB_bm;
		TC0_t* gt_ctrlA;
		TC0_t* gt_ctrlB;
		uint16_t period;
	private:

	//functions
	public:
	// This constructor creates a motor driver object
	Motor_Driver(PORT_t* p_port, uint8_t pinA, uint8_t pinB, uint8_t pinhA, uint8_t pinhB, TC0_t* t_ctrlA, TC0_t* t_ctrlB);
	// This method sets the duty cycle of the motor
	void set_duty_cycle(int8_t duty_cycle);
	~Motor_Driver();
	
	protected:
	private:

}; //Motor_Driver

#endif //__MOTOR_DRIVER_H__
