/*
 * GccApplication1.cpp
 *
 * Created: 10/24/2019 4:48:35 PM
 * Author : camkao
 * Tests ultrasonic sensor
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
static volatile int8_t rise_or_fall = 0;	//Flag to indicate rising (0) or falling (1) 
uint16_t echo_width;
uint16_t distance;
uint16_t start_echo;

void setUp16MhzExternalOsc()
{
	//16MHz external crystal
	OSC_XOSCCTRL = OSC_FRQRANGE_12TO16_gc | OSC_XOSCSEL_XTAL_16KCLK_gc;
	//Enable external oscillator
	OSC_CTRL |= OSC_XOSCEN_bm;
	//Wait for clock stabilization
	while(!(OSC_STATUS & OSC_XOSCRDY_bm));
	// Selects clock system as external clock
	// through change protection mechanism
	CCP = CCP_IOREG_gc;
	CLK_CTRL = CLK_SCLKSEL_XOSC_gc;
}


int main(void)
{
    
	setUp16MhzExternalOsc();
	
	PORTE.DIR |= (1<<0);		//Set PE0 out
	PORTE.DIR &= ~(1<<1);	    //Set PE1 in
	PORTE.DIR |= (1<<2);			//Set PE2 out

	PORTE.PIN1CTRL = PORT_ISC_BOTHEDGES_gc; //ISR will trigger whenever PC1 rises or falls
	PORTE.INT0MASK = PIN1_bm;
	PORTE.INTCTRL = PORT_INT0LVL_LO_gc;		//Set PE1 interrupt priority to low
	TCE1.PER = 0xFFFF;
	TCE1.CTRLA = ~TC1_CLKSEL_gm | TC_CLKSEL_DIV1_gc;
	PMIC_CTRL |= PMIC_LOLVLEN_bm;
	sei();	
	
	
	while (1)
	{
		_delay_us(10);		
		PORTE.OUT &= ~(1<<0);		//PC0 Low
		_delay_us(10000);
		distance = echo_width/16000 * 13504; //Distance in inches
		if (distance < 2)
		{
			PORTE.OUT |= (1<<2);
		}
		else
		{
			PORTE.OUT &= ~(1<<2);
		}
	}
}
	
	

ISR (PORTE_INT0_vect)    // Interrupt function
{
	if (rise_or_fall == 0)
	{
		//PORTE.OUT |= (1<<2);
		start_echo = TCE1.CNT;			//Set count register to zero for timing the pulse
		rise_or_fall = 1;
		
	}
	else
	{
		//PORTE.OUT &= ~(1<<2);
		echo_width = TCE1.CNT - start_echo;
		rise_or_fall = 0;
	}
	
	
}


