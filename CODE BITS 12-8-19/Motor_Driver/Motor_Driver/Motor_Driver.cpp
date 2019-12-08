/*
* Motor_Driver.cpp
*
* Created: 11/21/2019 4:13:58 PM
* Author: camka
*/


#include "Motor_Driver.h"

// default constructor
Motor_Driver::Motor_Driver(PORT_t* p_port, uint8_t pinA, uint8_t pinB, uint8_t pinhA, uint8_t pinhB, TC0_t* t_ctrlA, TC0_t* t_ctrlB):gp_port(p_port), gpinA_bm(1<<pinA), gpinB_bm(1<<pinB), gpinhA_bm(1<<pinhA), gpinhB_bm(1<<pinhB), gt_ctrlA(t_ctrlA), gt_ctrlB(t_ctrlB)
{
	
	gp_port->DIR |= gpinhA_bm;
	gp_port->DIR |= gpinhB_bm;
	gp_port->OUT |= gpinhA_bm;
	gp_port->OUT |= gpinhB_bm;
	gp_port->DIR |= gpinA_bm;
	gp_port->DIR |= gpinB_bm;
	gt_ctrlA->CTRLA = ~TC0_CLKSEL_gm | TC_CLKSEL_DIV1_gc;					//Set clock division in control register A to 1
	gt_ctrlA->PER = period;													//Set period in PER register
	gt_ctrlA->CTRLB = (~(TC0_CCAEN_bm | TC0_CCBEN_bm | TC0_CCCEN_bm | TC0_CCDEN_bm | TC0_WGMODE_gm)) | TC_WGMODE_SS_gc | TC0_CCAEN_bm | TC0_CCBEN_bm | TC0_CCCEN_bm | TC0_CCDEN_bm;	//Set single slope mode and enable channel
	gt_ctrlA->CTRLD = (~(TC0_EVACT_gm | TC0_EVSEL_gm)) | TC_EVACT_OFF_gc | TC_EVSEL_OFF_gc;
	*(&gt_ctrlA->CCA + pinA) = period/2;
	*(&gt_ctrlA->CCA + pinB) = period/2;

} //Motor_Driver

void Motor_Driver::set_duty_cycle(int8_t duty_cycle)
{
	if (duty_cycle>=0)
	{
		if (duty_cycle>100)
		{
			*(&gt_ctrlA->CCA + pinA) = period;
			*(&gt_ctrlA->CCA + pinB) = 0;
		}
		else
		{
			*(&gt_ctrlA->CCA + pinA) = period*(50+duty_cycle/2)/100;
			*(&gt_ctrlA->CCA + pinB) = period*(50-duty_cycle/2)/100;
		}
	}

	else
	{
		if (duty_cycle<-100)
		{
			*(&gt_ctrlA->CCA + pinA) = 0;
			*(&gt_ctrlA->CCA + pinB) = period;
			
		}
		else
		{
			*(&gt_ctrlA->CCA + pinA) = period*(50-duty_cycle/2)/100;
			*(&gt_ctrlA->CCA + pinB) = period*(50+duty_cycle/2)/100;
		}
	}
}

// default destructor
Motor_Driver::~Motor_Driver()
{
	
} //~Motor_Driver
