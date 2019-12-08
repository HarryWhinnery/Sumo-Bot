/*
* Motor_Driver.h
*
* Created: 11/21/2019 4:13:58 PM
* Author: camka
*/


#ifndef __MOTOR_DRIVER_H__
#define __MOTOR_DRIVER_H__
#include <avr/io.h>

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
	Motor_Driver(PORT_t* p_port, uint8_t pinA, uint8_t pinB, uint8_t pinhA, uint8_t pinhB, TC0_t* t_ctrlA, TC0_t* t_ctrlB);
	void set_duty_cycle(int8_t duty_cycle);
	~Motor_Driver();
	
	protected:
	private:
	//Motor_Driver(PORT_t* p_port, uint8_t pinA, uint8_t pinB, TC0_t* t_ctrlA, TC0_t* t_ctrlB);
	//Motor_Driver& operator=( const Motor_Driver &c );

}; //Motor_Driver

#endif //__MOTOR_DRIVER_H__
