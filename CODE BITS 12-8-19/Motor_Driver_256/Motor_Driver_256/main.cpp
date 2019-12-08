/*
 * Motor_Driver.cpp
 *
 * Created: 11/19/2019 9:32:59 AM
 * Author : camka
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>




int main(void)
{
	
	PORTD.DIR |= (1<<2);	//Set D2 out
	PORTD.DIR |= (1<<4);	//Set D4 out
	PORTD.OUT |= (1<<4);	//Set D4 to high
	TCD0.CTRLA = ~TC0_CLKSEL_gm | TC_CLKSEL_DIV1_gc;					//Set clock division in control register A to 1 
	TCD0.PER = 2000-1;													//Set period in PER register
	TCD0.CTRLB = (~(TC0_CCAEN_bm | TC0_CCBEN_bm | TC0_CCCEN_bm | TC0_CCDEN_bm | TC0_WGMODE_gm)) | TC_WGMODE_SS_gc | TC0_CCAEN_bm | TC0_CCBEN_bm | TC0_CCCEN_bm | TC0_CCDEN_bm;	//Set single slope mode and enable channel
	TCD0.CTRLD = (~(TC0_EVACT_gm | TC0_EVSEL_gm)) | TC_EVACT_OFF_gc | TC_EVSEL_OFF_gc;	//Capture event off
	TCD0.CCA = 1000;			 					//Set duty cycle (D0) 
	TCD0.CCB = 1000;			 					//Set duty cycle (D1)
	TCD0.CCC = 1800;								//Set duty cycle (D2)
	
	
	
	
while (1) 
    {
			
		
    }
}

