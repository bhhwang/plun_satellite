/*
 * plunbase.h
 *
 *  Created on: 2014. 7. 17.
 *      Author: Byunghun Hwang <bhhwang@nsynapse.com>
 *      Desc. : This is customized for PLUN-Satellite
 */

#ifndef PLUNBASE_H_
#define PLUNBASE_H_


/*
 * user defined
 */
#define USE_UART
#define USE_WIFI	//cc3000
#define OSC_CLOCK	16000000L	//osciilator clock


#include <stdint.h>
#include <stdbool.h>

/*
 * Note : User have to install the TIVAWare(2.1.0.12573) and set the path
 */
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"

#include "utils/uartstdio.h"

#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"

#include "dispatcher.h"	//uart dispatcher
#include "spi.h"

/*#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "inc/hw_memmap.h"*/

#ifdef USE_UART
	#define UART_BAUDRATE	115200
	#define UART_PORT	0
#endif

#ifdef USE_WIFI
	#define SSID = "nsynapse";
	#define PASS = "ghkdqudgns";
#endif



/*
 * initialize
 */
void init_satellite()
{
	FPUEnable();
	FPULazyStackingEnable();

	MAP_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);	//50MHz

	//MAP_IntMasterEnable();

	/*
	 * Enable peripherals
	 */
#ifdef USE_UART
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
#endif

#ifdef USE_WIFI
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);	//for IRQ and SW_EN
#endif

	/*
	 * configure
	 */
#ifdef USE_UART
	MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
	MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
	MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	UARTStdioConfig(UART_PORT, UART_BAUDRATE, SysCtlClockGet());
#endif

#ifdef USE_WIFI
	MAP_GPIOIntDisable(GPIO_PORTB_BASE, 0xFF);	//interrupt disable

	MAP_GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_2);	//IRQ as input
	GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	MAP_GPIOIntTypeSet(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_FALLING_EDGE);

	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_5);
	MAP_GPIODirModeSet(GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_DIR_MODE_OUT);
	MAP_GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
	MAP_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, PIN_LOW);	//disable?
	SysCtlDelay(600000);
	SysCtlDelay(600000);
	SysCtlDelay(600000); //why?
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);	//for SPI
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_0);
	GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	MAP_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, PIN_HIGH);	//chip select

	MAP_GPIOIntEnable(GPIO_PORTB_BASE, GPIO_PIN_2);	//interrupt enable

	SpiCleanGPIOISR();
	MAP_IntEnable(INT_GPIOB);
#endif
}


#endif /* PLUNBASE_H_ */
