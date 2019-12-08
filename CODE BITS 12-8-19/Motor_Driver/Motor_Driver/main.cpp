/*
 * main.cpp
 *
 * Created: 11/19/2019 9:32:59 AM
 * Author : camka
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>




int main(void)
{
	
	PORTC.DIR |= (1<<7);
	PORTC.OUT |= (1<<7);
	
	PORTD.DIR |= (1<<2);	//Set D2 out
	PORTD.DIR |= (1<<3);	//Set D3 out
	PORTD.DIR |= (1<<4);	//Set D4 out
	PORTD.OUT |= (1<<4);	//Set D4 to high
	TCD0.CTRLA = ~TC0_CLKSEL_gm | TC_CLKSEL_DIV1_gc;				//Set clock division in control register A to 1 
	TCD0.PER = 200;													//Set period in PER register
	TCD0.CTRLB = (~(TC0_CCAEN_bm | TC0_CCBEN_bm | TC0_CCCEN_bm | TC0_CCDEN_bm | TC0_WGMODE_gm)) | TC_WGMODE_SS_gc | TC0_CCAEN_bm | TC0_CCBEN_bm | TC0_CCCEN_bm | TC0_CCDEN_bm;	//Set single slope mode and enable channel
	TCD0.CTRLD = (~(TC0_EVACT_gm | TC0_EVSEL_gm)) | TC_EVACT_OFF_gc | TC_EVSEL_OFF_gc;	//Capture event off
	TCD0.CCC = 100;			 					//Set duty cycle (D2)
	TCD0.CCD = 180;								//Set duty cycle (D3)
	
	
	
	
while (1) 
    {
			
		
    }
}

