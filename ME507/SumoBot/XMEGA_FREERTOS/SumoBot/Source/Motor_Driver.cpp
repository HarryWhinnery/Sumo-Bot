//**************************************************************************************
/** \file Motor_Driver.cpp
 *    This file contains source code for a motor driver class for a board using two 
 *    half bridge motor drivers. The motor's speed can be controlled through the
 *    set_duty_cycle function.
 */
//**************************************************************************************


#include "Motor_Driver.h"

//-------------------------------------------------------------------------------------
/** This constructor creates a new motor driver.
 *  @param p_port The port of the microcontroller that will be outputting PWM to motor driver
 *  @param pinA The PWM output pin for one half bridge
 *  @param pinB The PWM output pin for second half bridge
 *  @param pinhA The enable pin for one half bridge
 *  @param pinhB The enable pin for second half bridge
 *  @param t_ctrlA The timer/counter for the PWM for one half bridge
 *  @param t_ctrlB The timer/counter for the PWM for second half bridge
 */

Motor_Driver::Motor_Driver(PORT_t* p_port, uint8_t pinA, uint8_t pinB, uint8_t pinhA, uint8_t pinhB, TC0_t* t_ctrlA, TC0_t* t_ctrlB):gp_port(p_port), gpinA_bm(1<<pinA), gpinB_bm(1<<pinB), gpinhA_bm(1<<pinhA), gpinhB_bm(1<<pinhB), gt_ctrlA(t_ctrlA), gt_ctrlB(t_ctrlB)
{
	// Saves pinA and pinB for use in set_duty_cycle function
	pin1 = pinA;
	pin2 = pinB;
	
	// Sets period to achieve reasonable frequency for motor function (and hearing)
	period = 1000;
	
	// Sets enable pins to output and high
	gp_port->DIR |= gpinhA_bm;	
	gp_port->DIR |= gpinhB_bm;
	gp_port->OUT |= gpinhA_bm;
	gp_port->OUT |= gpinhB_bm;
	
	// Sets PWM pins to output
	gp_port->DIR |= gpinA_bm;
	gp_port->DIR |= gpinB_bm;
	
	// Initializes timer counter for PWM output (assumes both pins use the same timer counter)
	gt_ctrlA->CTRLA = ~TC0_CLKSEL_gm | TC_CLKSEL_DIV1_gc;					//Set clock division in control register A to 1
	gt_ctrlA->PER = period;													//Set period in PER register
	gt_ctrlA->CTRLB = (~(TC0_CCAEN_bm | TC0_CCBEN_bm | TC0_CCCEN_bm | TC0_CCDEN_bm | TC0_WGMODE_gm)) | TC_WGMODE_SS_gc | TC0_CCAEN_bm | TC0_CCBEN_bm | TC0_CCCEN_bm | TC0_CCDEN_bm;	//Set single slope mode and enable channel
	gt_ctrlA->CTRLD = (~(TC0_EVACT_gm | TC0_EVSEL_gm)) | TC_EVACT_OFF_gc | TC_EVSEL_OFF_gc;
	
	// Sets duty cycle for both pins to be 0 to disable motor
	*(&gt_ctrlA->CCA + pinA) = 0;
	*(&gt_ctrlA->CCA + pinB) = 0;

} //Motor_Driver

//-------------------------------------------------------------------------------------
/** This method sets the duty cycle of the motor.
 *  @param duty_cycle The desired duty cycle of the motor, will saturate if input above 100 or below -100
 */

void Motor_Driver::set_duty_cycle(int8_t duty_cycle)
{
	if (duty_cycle>=0)
	{
		// Saturates the duty cycle to 100 if input is greater
		if (duty_cycle>=100)
		{
			*(&gt_ctrlA->CCA + pin1) = period;
			*(&gt_ctrlA->CCA + pin2) = 0;
		}
		else
		{
			*(&gt_ctrlA->CCA + pin1) = period*(duty_cycle)/100;
			*(&gt_ctrlA->CCA + pin2) = 0;
		}
	}
	else
	{
		// Saturates the duty cycle to -100 if input is less
		if (duty_cycle<=-100)
		{
			*(&gt_ctrlA->CCA + pin1) = 0;
			*(&gt_ctrlA->CCA + pin2) = period;
		}
		else
		{
			*(&gt_ctrlA->CCA + pin1) = 0;
			*(&gt_ctrlA->CCA + pin2) = period*(-duty_cycle)/100;
		}
	}
	
	
}

// default destructor
Motor_Driver::~Motor_Driver()
{
	
} //~Motor_Driver
