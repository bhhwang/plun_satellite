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
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_nvic.h"
#include "inc/hw_ints.h"

/*
 * include driver
 */
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/flash.h"
#include "driverlib/eeprom.h"
#include "driverlib/ssi.h"
#include "driverlib/cpu.h"
#include "driverlib/fpu.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/pin_map.h"

/*
 * include utility
 */
#include "utils/ustdlib.h"
#include "utils/uartstdio.h"

/*
 * for plun platform
 */
#include "settings.h"




#define	LED_GREEN	GPIO_PORTF_BASE, GPIO_PIN_3
#define LED_BLUE	GPIO_PORTF_BASE, GPIO_PIN_2
#define LED_RED		GPIO_PORTF_BASE, GPIO_PIN_1
#define LED_IND		GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3


/*#define PLATFORM_VERSION                        5
#define CC3000_APP_BUFFER_SIZE                  5
#define CC3000_RX_BUFFER_OVERHEAD_SIZE          20
#define SL_VERSION_LENGTH                       11
#define NETAPP_IPCONFIG_MAC_OFFSET              20

#define NUM_CHANNELS                            13*/

//*****************************************************************************
//
// Return codes from wlan_ioctl_statusget() which appear to be missing from
// the CC3000 SDK.
//
//*****************************************************************************
#define WLAN_STATUS_DISCONNECTED                0
#define WLAN_STATUS_SCANNING                    1
#define WLAN_STATUS_CONNECTING                  2
#define WLAN_STATUS_CONNECTED                   3

//*****************************************************************************
//
// The structure returned by a call to wlan_ioctl_get_scan_results.
//
//*****************************************************************************
typedef struct
{
    uint32_t ui32NumNetworks;
    uint32_t ui32Status;
    uint8_t  ui8ValidRSSI;
    uint8_t  ui8SecuritySSIDLen;
    uint16_t ui16Time;
    char     pcSSID[32];
    char     pcBSSID[6];
}
tScanResult;

//*****************************************************************************
//
// Status values found in the tScanResult ui32Status field.
//
//*****************************************************************************
#define SCAN_AGED_RESULT                            0
#define SCAN_RESULT_VALID                           1
#define SCAN_NO_RESULT                              2

//*****************************************************************************
//
// Masks related to values found in the tScanResult ui8ValidRSSI field.
//
//*****************************************************************************
#define SCAN_IS_VALID                               0x01
#define SCAN_RSSI_MASK                              0xFE

//*****************************************************************************
//
// Masks and labels related to values found in the tScanResult
// ui8SecuritySSIDLen field.
//
//*****************************************************************************
#define SCAN_SEC_MASK                               0x03
#define SCAN_SEC_SHIFT                                 0
#define SCAN_SEC_OPEN                               0x00
#define SCAN_SEC_WEP                                0x40
#define SCAN_SEC_WPA                                0x80
#define SCAN_SEC_WPA2                               0xC0
#define SCAN_SEC_INDEX(x) (((x) & SCAN_SEC_MASK) >> SCAN_SEC_SHIFT)

char *g_ppcSecurity[] = {"Open", "WEP", "WPA", "WPA2"};

//*****************************************************************************
//
// Mask, shift and macro to extract the SSID length from the ui8SecuritySSIDLen
// field.
//
//*****************************************************************************
#define SCAN_SSID_LEN_MASK                          0xFC
#define SCAN_SSID_LEN_SHIFT                            2
#define SCAN_SSID_LEN(x) (((x) & SCAN_SSID_LEN_MASK) >> SCAN_SSID_LEN_SHIFT)

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



/*
 * setting up
 */
/*void setup()
{

#ifdef USE_UART0
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
	ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
	ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	UARTStdioConfig(UART0_PORT, UART0_BAUDRATE, SysCtlClockGet());
#endif

#ifdef USE_CC3000
	init_spi(1000000, SysCtlClockGet());	//1MHz SPI for connecting CC3000
#endif

	ROM_IntMasterEnable();

	wlan_init(CC3000_AsyncCallback, sendWLFWPatch, sendDriverPatch,sendBootLoaderPatch,
			ReadWlanInterruptPin, WlanInterruptEnable, WlanInterruptDisable,WriteWlanPin);
	wlan_start(0);
	turnLedOn(RED_LED);
	wlan_set_event_mask(HCI_EVNT_WLAN_KEEPALIVE | HCI_EVNT_WLAN_UNSOL_INIT | HCI_EVNT_WLAN_ASYNC_PING_REPORT);

	//ROM_SysCtlDelay((SysCtlClockGet() / 10) / 3);

	InitSysTick();

}*/

/*
 * functions
 */
void serial_begin(uint32_t port, uint32_t baudrate)
{
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
	ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
	ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	UARTStdioConfig(port, baudrate, SysCtlClockGet());
}

#define SYSTICKHZ	100
#define F_CPU		80000000L
#define SYSTICK_INT_PRIORITY    0x80
/*
 * setup
 */
void setup()
{
	//MAP_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);	//80MHz
	SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	ROM_SysTickPeriodSet(F_CPU / SYSTICKHZ);
	ROM_SysTickEnable();
	ROM_IntPrioritySet(FAULT_SYSTICK, SYSTICK_INT_PRIORITY);
	ROM_SysTickIntEnable();

	serial_begin(0, 115200);
}

/*
 * process
 */
void loop()
{
	while(1)
	{
		UARTprintf("test\n");
		SysCtlDelay(SysCtlClockGet());
	}
}

int main(void)
{
	setup();
	loop();
}
