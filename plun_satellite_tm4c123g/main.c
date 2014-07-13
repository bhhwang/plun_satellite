/*
 * plun satelite firmware v.0.0.1 for TI's TM4C123GH6PM Launchpad
 * programmed by Byunghun Hwang <bhhwang@nsynapse.com>
 * Copyright (c) Nsynapse Inc. All rights reserved.
 *
 * Note : This firmware can be used for TM4C123GH6PM Launchpad with CC3000 WiFi module.
 */
#include <stdint.h>
#include <stdbool.h>
#include <inc/hw_types.h>
#include <inc/hw_memmap.h>
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>

void setup()
{
	/*
	 * use main oscillator(16MHz) + use pll + devide by 4 : system clock = 50MHz
	 */
	SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
}

int main(void)
{

	//setup
	setup();

	uint8_t ui8LED = 2;

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	while(1)
	{
		// Turn on the LED
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, ui8LED);
		// Delay for a bit
		SysCtlDelay(2000000);
		// Cycle through Red, Green and Blue LEDs
		if (ui8LED == 8) {ui8LED = 2;} else {ui8LED = ui8LED*2;}
	}
}
