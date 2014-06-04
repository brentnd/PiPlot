#include "Config.h"

/*
 * Initialize clock, system, GPIO
 */
void Initialize()
{
	InitClock();
	InitSysTick();
	InitGPIO();
	InitUARTs();
}

void InitGPIO()
{
	//enable Clocks to all ports
	SIM_SCGC5 |=
			SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK
					| SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;

	//Setup Pins as GPIO
	PORTE_PCR21 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;
	PORTE_PCR20 = PORT_PCR_MUX(1);

	//Setup the output pins
	//GPIOB_PDDR = PIN;
	//GPIOE_PDDR = PIN;
	//GPIOD_PDDR |= PIN;

	//Port for Pushbuttons
	//PORTC_PCR13 = PORT_PCR_MUX(1);
	//PORTC_PCR17 = PORT_PCR_MUX(1);

	//Ports for LEDs
	//PORTD_PCR1 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;
	//PORTB_PCR8 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;
	//PORTB_PCR9 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;
	//PORTB_PCR10 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;
	//PORTB_PCR11 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;
}
