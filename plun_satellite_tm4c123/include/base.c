/*
 * base.c
 *
 *  Created on: 2014. 7. 20.
 *      Author: Byunghun Hwang <bhhwang@nsynapse.com>
 *      Desc. : Plun system base functions
 */

#ifndef BASE_C_
#define BASE_C_


#include "plun.h"

void init_worker()
{
	SysTickPeriodSet(SysCtlClockGet()/4);	//250ms (maximum 16,777,216, about 250ms)
	SysTickIntEnable();
	SysTickEnable();
}

/*
 * initialize tm4c
 */
void init_satellite()
{
	FPUEnable();
	FPULazyStackingEnable();

	/*
	 * init clock
	 */
	MAP_SysCtlClockSet(SYSCTL_SYSDIV_3 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);	//66.6..MHz

	MAP_IntMasterEnable();

	/*
	 * Enable peripherals
	 */
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);	//for LED indication

	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);	//for UART
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);	//for IRQ and SW_EN
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);	//for SPI


	/*
	 * configure
	 */
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	MAP_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, SIGNAL_LOW);	//off

	MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
	MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
	MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	UARTStdioConfig(UART_PORT, UART_BAUDRATE, SysCtlClockGet());


	MAP_GPIOIntDisable(GPIO_PORTB_BASE, SIGNAL_HIGH);	//interrupt disable

	MAP_GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_2);	//IRQ as input
	MAP_GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	MAP_GPIOIntTypeSet(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_FALLING_EDGE);		//enable interrupt

	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_5);	//sw enable
	MAP_GPIODirModeSet(GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_DIR_MODE_OUT);
	MAP_GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);

	MAP_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, SIGNAL_LOW);

	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_0);

	MAP_GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	MAP_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, SIGNAL_HIGH);	//chip select

	MAP_GPIOIntEnable(GPIO_PORTB_BASE, GPIO_PIN_2);	//enable interrupt for WLAN_IRQ pin

	SpiCleanGPIOISR();	//clear interrupt status

	MAP_IntEnable(INT_GPIOB);	//spi


	init_worker();

	setState(READY);
}



#endif /* BASE_C_ */
