/*
 * task_IR.cpp
 *
 * Created: 11/5/2019 7:53:37 PM
 * Author : camka
 */ 

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/wdt.h>                        // Watchdog timer header

#include "shared_data_sender.h"
#include "shared_data_receiver.h"
#include "IR_sensor.h"
uint8_t test = 1;


int main (void)
{

	
	/* Replace with your application code */
	PORTA.DIR |= (1<<4);		//Set PA4 to output (LED)

	IR_sensor test_IR_sensor (&PORTA, 5);
    
	while (1) 
    {
		
		if (test_IR_sensor.read())
		{
			PORTA.OUT = 0<<4;
		}
		else
		{
			PORTA.OUT = 1<<4;
		}
		
    }
}



