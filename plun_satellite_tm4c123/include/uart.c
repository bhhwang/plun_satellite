/*
 * uart.c
 *
 *  Created on: 2014. 7. 16.
 *      Author: Byunghun Hwang <bhhwang@nsynapse.com>
 *      Desc. : UART functions for satellite-tm4c123
 */

#include "uart.h"

#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "inc/hw_memmap.h"
#include "def.h"

void serial_begin(uint32_t port, uint32_t baudrate)
{
#ifdef USE_UART0

	/*
	 * Enable the GPIO Peripheral used by the UART.
	 */
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	/*
	 * Enable UART0
	 */
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

	/*
	 * Configure GPIO Pins for UART mode.
	 */
	ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
	ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
	ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	/*
	 * Use the internal 16MHz oscillator as the UART clock source.
	 */
	UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

	/*
	 * Initialize the UART for console I/O.
	 */
	UARTStdioConfig(UART0_PORT, UART0_BAUDRATE, OSC_CLOCK);

#endif
}

