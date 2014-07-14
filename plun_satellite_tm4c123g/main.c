/*
 * plun satellite (TI tm4c123g) firmware for TI's TM4C123GH6PM Launchpad
 * programmed by Byunghun Hwang <bhhwang@nsynapse.com>
 * Copyright (c) Nsynapse Inc. All rights reserved.
 * Version : 0.0.1
 * Date : 2014. 7. 14
 *
 * Note : This firmware can be used for TM4C123GH6PM Launchpad with CC3000 WiFi module.
 */


#include <stdint.h>
#include <stdbool.h>
#include <inc/tm4c123gh6pm.h>
#include <inc/hw_types.h>
#include <inc/hw_memmap.h>
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include <driverlib/interrupt.h>
#include <driverlib/gpio.h>
#include <driverlib/timer.h>

void Timer0IntHandler(void)
{
	// Clear the timer interrupt
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

	// Read the current state of the GPIO pin and
	// write back the opposite state
	if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2))
	{
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
	}
	else
	{
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 4);
	}
}

void setup()
{
	/*
	 * use main oscillator(16MHz) + use PLL(400MHz) + devide by 4 : system clock = 50MHz
	 */
	SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	/*
	 * use GPIO F (output 1,2,3)
	 */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

	/*
	 * Timer 0
	 */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

	uint32_t ui32Period;
	ui32Period = SysCtlClockGet();
	TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period -1);

	IntEnable(INT_TIMER0A);
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	IntMasterEnable();

	TimerEnable(TIMER0_BASE, TIMER_A);
}

int main(void)
{
	setup();
	while(1) {};

}
