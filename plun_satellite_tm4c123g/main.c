/*
 * plun satellite (TI TM4C123G) firmware for TI's TM4C123GH6PM Launchpad
 * programmed by Byunghun Hwang <bhhwang@nsynapse.com>
 * Copyright (c) Nsynapse Inc. All rights reserved.
 * Version : 0.0.1
 * Date : 2014. 7. 14
 *
 * Note : This firmware can be used for TI's TM4C123GH6PM Launchpad with CC3000 WiFi boostpack.
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
#include <driverlib/flash.h>
#include <driverlib/eeprom.h>
#include <utils/uartstdio.h>


#include "wlan.h"
#include <cc3000/src/host_driver/core_driver/evnt_handler.h>
#include <nvmem.h>
#include "common/cc3000_common.h"
#include <netapp.h>
#include <cc3000/src/spi/spi.h>
#include "common/hci.h"
#include <cc3000/src/spi/spi_version.h>
#include <cc3000/drivers/dk-tm4c123g/board.h>
#include <host_driver_version.h>
#include <security.h>

#define	LED_GREEN	GPIO_PORTF_BASE, GPIO_PIN_3
#define LED_BLUE	GPIO_PORTF_BASE, GPIO_PIN_2
#define LED_RED		GPIO_PORTF_BASE, GPIO_PIN_1
#define LED_IND		GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3


const char ssid[] = "nsynapse";
const char pass[] = "ghkdqudgns";



/*
 * Timer0 Interrupt handler
 * @remark	must set this function into the startup_css.c file(vector table)
 */
void Timer0IntHandler(void)
{
	/*
	 * Clear Timer0
	 */
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

	if(GPIOPinRead(LED_GREEN))
		GPIOPinWrite(LED_IND, 0);
	else
		GPIOPinWrite(LED_GREEN, GPIO_PIN_3);
}

void setup()
{
	/*
	 * use main oscillator(16MHz) + use PLL(400MHz) + devided by 4 + devided by 2(default) : system clock = 50MHz
	 */
	SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	/*
	 * use GPIO F (output 1,2,3)
	 */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

	/*
	 * Timer 0 (periodic)
	 */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);


	/*
	 * timer 0 period set to 500ms
	 */
	uint32_t ui32Period = SysCtlClockGet()/2;
	TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period -1);

	/*
	 * Enable interrupt
	 */
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
