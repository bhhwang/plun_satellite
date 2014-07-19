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
#define HIGH	0xff
#define LOW		!0XFF


#include <stdint.h>
#include <stdbool.h>
#include "inth.h"

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
#include "driverlib/systick.h"

/*
 * default
 */
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"

#define WORKER_INT_TIME	100	//ms, must under 250ms

/*
 * definition for UART
 */
#ifdef USE_UART
#include "utils/uartstdio.h"
#include "dispatcher.h"	//uart dispatcher

#define UART_BAUDRATE	115200
#define UART_PORT	0
#endif

/*
 * definition for WIFI
 */
#ifdef USE_WIFI
#include "spi.h"
#include "wlan.h"
#include "evnt_handler.h"
#include "socket.h"
#include "hci.h"
#include "netapp.h"
#include "security.h"
#endif


typedef struct structIPAddress { uint8_t ip[4]; } IPAddress;


#ifdef USE_WIFI
volatile unsigned long isConnectedAP;
volatile unsigned long ulSmartConfigFinished,ulCC3000DHCP, OkToDoShutDown, ulCC3000DHCP_configured, ulCC3000WasConnected;
char* sendDriverPatch(unsigned long *Length)
{
    *Length = 0;
    return((char *)0);
}

char* sendBootLoaderPatch(unsigned long *Length)
{
    *Length = 0;
    return((char *)0);
}

char* sendWLFWPatch(unsigned long *Length)
{
    *Length = 0;
    return((char *)0);
}

#define NETAPP_IPCONFIG_MAC_OFFSET				(20)
void CC3000_AsyncCallback(long lEventType, char *data, unsigned char length)
{

	if (lEventType == HCI_EVNT_WLAN_ASYNC_SIMPLE_CONFIG_DONE)
		ulSmartConfigFinished = 1;

	if (lEventType == HCI_EVNT_WLAN_UNSOL_CONNECT)
		isConnectedAP = 1;

	if (lEventType == HCI_EVNT_WLAN_UNSOL_DISCONNECT)
	{
		isConnectedAP = 0;
		ulCC3000DHCP      = 0;
		ulCC3000DHCP_configured = 0;
	}

	if (lEventType == HCI_EVNT_WLAN_UNSOL_DHCP)
	{
		// Notes:
		// 1) IP config parameters are received swapped
		// 2) IP config parameters are valid only if status is OK, i.e. ulCC3000DHCP becomes 1

		// only if status is OK, the flag is set to 1 and the addresses are valid
		if ( *(data + NETAPP_IPCONFIG_MAC_OFFSET) == 0)
			ulCC3000DHCP = 1;
		else
			ulCC3000DHCP = 0;
	}

	if (lEventType == HCI_EVENT_CC3000_CAN_SHUT_DOWN)
	{
		OkToDoShutDown = 1;
	}
}

long ReadWlanInterruptPin(void){ return MAP_GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_2); }
void WlanInterruptEnable(){ MAP_GPIOIntEnable(GPIO_PORTB_BASE, GPIO_PIN_2); }
void WlanInterruptDisable(){ MAP_GPIOIntDisable(GPIO_PORTB_BASE, GPIO_PIN_2); }
void WriteWlanPin( unsigned char val ){ val?MAP_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, HIGH):MAP_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, LOW); }

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

#define SCAN_IS_VALID                               0x01
#define SCAN_RSSI_MASK                              0xFE
#define SCAN_AGED_RESULT                            0
#define SCAN_RESULT_VALID                           1
#define SCAN_NO_RESULT                              2
#define SCAN_SEC_MASK                               0x03
#define SCAN_SEC_SHIFT                                 0
#define SCAN_SEC_OPEN                               0x00
#define SCAN_SEC_WEP                                0x40
#define SCAN_SEC_WPA                                0x80
#define SCAN_SEC_WPA2                               0xC0
#define SCAN_SEC_INDEX(x) (((x) & SCAN_SEC_MASK) >> SCAN_SEC_SHIFT)
#define SCAN_SSID_LEN_MASK                          0xFC
#define SCAN_SSID_LEN_SHIFT                            2
#define SCAN_SSID_LEN(x) (((x) & SCAN_SSID_LEN_MASK) >> SCAN_SSID_LEN_SHIFT)
char *g_ppcSecurity[] = {"Open", "WEP", "WPA", "WPA2"};

void wifi_scan()
{
	tScanResult sScanResult;
    long lRetcode, lLoop, lCount;
    unsigned long pulIntervalList[10];

    for(lLoop = 0; lLoop < 10; lLoop++)
        pulIntervalList[lLoop] = 2000;

    UARTprintf("Setting SSID scan parameters... ");
    lRetcode = wlan_ioctl_set_scan_params(1, 20, 30, 2, 0x7FF, -80, 0, 205, pulIntervalList);

    UARTprintf("Done\n");

    if(lRetcode == 0)
	{
		//
		// Yes. Wait for the scan to stop.
		//
		UARTprintf("Scanning...\n");

		do
		{
			lRetcode = wlan_ioctl_statusget();
		}
		while(lRetcode);

		UARTprintf("Scan completed. Querying results...\n");

		//
		// Retrieve the first scan result to allow us to determine how many
		// APs were found (if any).
		//
		lRetcode = wlan_ioctl_get_scan_results(0, (unsigned char *)&sScanResult);
		if(lRetcode == 0)
		{
			//
			// We got the first scan result.  Did the scan complete
			// successfully?
			//
			if((sScanResult.ui32Status == SCAN_NO_RESULT) ||
			   (sScanResult.ui32NumNetworks == 0))
			{
				//
				// We found no networks.
				//
				UARTprintf("No wireless networks found.\n");
			}
			else
			{
				//
				// We found something so read the rest of the results and
				// dump the information.
				//
				UARTprintf("Found %d networks.\n\n", sScanResult.ui32NumNetworks);

				//
				// Remember the number of networks that were found.
				//
				lLoop = (long)sScanResult.ui32NumNetworks;

				//
				// Initialize our network number counter.
				//
				lCount = 1;

				do
				{
					uint32_t ui32SSIDLen;

					//
					// Ensure that the SSID is NULL terminated.
					//
					ui32SSIDLen = SCAN_SSID_LEN(sScanResult.ui8SecuritySSIDLen);

					//
					// If the SSID length we decode is larger than 31,
					// something's wrong but clip the length accordingly. We
					// clip at 32 characters to ensure that we don't overwrite
					// the start of the BSSID field which appears next in
					// memory.
					//
					if(ui32SSIDLen > 31)
					{
						ui32SSIDLen = 31;
					}

					sScanResult.pcSSID[ui32SSIDLen] = '\0';

					//
					// Print information on the current network.
					//
					if(sScanResult.ui8ValidRSSI & SCAN_IS_VALID)
					{
						//
						// Extract the security information from the returned
						// structure.
						//
						ui32SSIDLen =
								SCAN_SEC_INDEX(sScanResult.ui8SecuritySSIDLen);

						UARTprintf("%2d: %02x%02x%02x%02x%02x%02x %s %s\n",
								   lCount,
								   sScanResult.pcBSSID[0],
								   sScanResult.pcBSSID[1],
								   sScanResult.pcBSSID[2],
								   sScanResult.pcBSSID[3],
								   sScanResult.pcBSSID[4],
								   sScanResult.pcBSSID[5],
								   g_ppcSecurity[ui32SSIDLen],
								   sScanResult.pcSSID);
					}
					else
					{
						//
						// The structure passed back to us was marked as
						// invalid.
						//
						UARTprintf("%d - Invalid entry received!\n", lCount);
					}

					//
					// Decrement our network counter.
					//
					lLoop--;

					//
					// Increment our network number count.
					//
					lCount++;

					//
					// Get the information on the next network if there is
					// another one to get.
					//
					if(lLoop)
					{
						lRetcode = wlan_ioctl_get_scan_results(0,
												(unsigned char *)&sScanResult);
					}
				}
				while(lLoop && (lRetcode == 0));
			}
		}
		else
		{
			UARTprintf("Error from wlan_ioctl_get_scan_results!\n");
		}
	}
	else
	{
		//
		// Tell the user an error was reported.
		//
		UARTprintf("Error from wlan_ioctl_set_scan_params!\n");
	}

	UARTprintf("\nScanning completed.\n");
}
#endif


/*
 * initialize
 */
void init_wifi();		//initialize WiFi(CC3000 module)
void init_satellite();	//system initialization
void init_worker();		//system tick handler for plun worker

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

#ifdef USE_UART
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
#endif

#ifdef USE_WIFI
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);	//for IRQ and SW_EN
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);	//for SPI
#endif

	/*
	 * configure
	 */
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	MAP_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, LOW);	//off

#ifdef USE_UART
	MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
	MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
	MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	UARTStdioConfig(UART_PORT, UART_BAUDRATE, SysCtlClockGet());
#endif

#ifdef USE_WIFI
	MAP_GPIOIntDisable(GPIO_PORTB_BASE, HIGH);	//interrupt disable

	MAP_GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_2);	//IRQ as input
	MAP_GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	MAP_GPIOIntTypeSet(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_FALLING_EDGE);		//enable interrupt

	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_5);	//sw enable
	MAP_GPIODirModeSet(GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_DIR_MODE_OUT);
	MAP_GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);

	MAP_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, LOW);

	//MAP_SysCtlDelay(600000);	//wait for ..

	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_0);

	MAP_GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	MAP_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, HIGH);	//chip select

	MAP_GPIOIntEnable(GPIO_PORTB_BASE, GPIO_PIN_2);	//enable interrupt for WLAN_IRQ pin

	SpiCleanGPIOISR();	//clear inerrupt status

	MAP_IntEnable(INT_GPIOB);	//spi

#endif

	init_worker();
	setState(READY);
}

void init_wifi()
{
	init_spi(1000000, SysCtlClockGet());

	//MAP_IntMasterEnable();	//enable processor interrupt

	wlan_init(CC3000_AsyncCallback, sendWLFWPatch, sendDriverPatch, sendBootLoaderPatch,
				ReadWlanInterruptPin, WlanInterruptEnable, WlanInterruptDisable, WriteWlanPin);
	wlan_start(0);
	wlan_ioctl_set_connection_policy(0, 0, 0);	//does not attempt to connect to a previously configuration
	wlan_set_event_mask(HCI_EVNT_WLAN_KEEPALIVE | HCI_EVNT_WLAN_UNSOL_INIT | HCI_EVNT_WLAN_ASYNC_PING_REPORT);

	//MAP_SysCtlDelay(2000000);
	init_worker();
}

void init_worker()
{
	SysTickPeriodSet(SysCtlClockGet()/10);	//100ms tick
	SysTickIntEnable();
	SysTickEnable();
}

/*
 * for WiFi
 */
#include "wlan.h"

void connect_ap(char* ssid, const char* pass)
{
	UARTprintf("connecting to AP...\n");
	init_spi(1000000, SysCtlClockGet());
	ulCC3000WasConnected = 0;

	wlan_init(CC3000_AsyncCallback, sendWLFWPatch, sendDriverPatch, sendBootLoaderPatch,
					ReadWlanInterruptPin, WlanInterruptEnable, WlanInterruptDisable, WriteWlanPin);
	wlan_start(0);
	wlan_ioctl_set_connection_policy(0, 0, 0);	//does not attempt to connect to a previously configuration
	wlan_set_event_mask(HCI_EVNT_WLAN_KEEPALIVE | HCI_EVNT_WLAN_UNSOL_INIT | HCI_EVNT_WLAN_ASYNC_PING_REPORT);

	uint32_t aucDHCP = 14400;	uint32_t aucARP = 3600;	uint32_t aucKeepalive = 10;	uint32_t aucInactivity = 0;
	netapp_timeout_values((unsigned long*)&aucDHCP, (unsigned long*)&aucARP, (unsigned long*)&aucKeepalive, (unsigned long*)&aucInactivity);

	wlan_connect(WLAN_SEC_WPA2, ssid, strlen(ssid), NULL, (unsigned char *)pass, strlen((char *)(pass)));

	while(isConnectedAP==0)	{ MAP_SysCtlDelay(10000); }	//wait until connecting

	setState(DHCP_CONNECTED);
}

void disconnect_ap(){ wlan_disconnect(); }

void getLocalIP(IPAddress* ip)
{
	tNetappIpconfigRetArgs config;
	netapp_ipconfig(&config);

	ip->ip[3] = config.aucIP[0];
	ip->ip[2] = config.aucIP[1];
	ip->ip[1] = config.aucIP[2];
	ip->ip[0] = config.aucIP[3];
}

void getSubnetMask(IPAddress* ip)
{
	tNetappIpconfigRetArgs config;
	netapp_ipconfig(&config);

	ip->ip[3] = config.aucSubnetMask[0];
	ip->ip[2] = config.aucSubnetMask[1];
	ip->ip[1] = config.aucSubnetMask[2];
	ip->ip[0] = config.aucSubnetMask[3];
}

void getGateway(IPAddress* ip)
{
	tNetappIpconfigRetArgs config;
	netapp_ipconfig(&config);

	ip->ip[3] = config.aucDefaultGateway[0];
	ip->ip[2] = config.aucDefaultGateway[1];
	ip->ip[1] = config.aucDefaultGateway[2];
	ip->ip[0] = config.aucDefaultGateway[3];
}

void getBroadcast(IPAddress* ip)
{
	IPAddress DeviceIP; getLocalIP(&DeviceIP);
	IPAddress SubnetMask; getSubnetMask(&SubnetMask);

	ip->ip[0] = (DeviceIP.ip[0]|~SubnetMask.ip[0]);
	ip->ip[1] = (DeviceIP.ip[1]|~SubnetMask.ip[1]);
	ip->ip[2] = (DeviceIP.ip[2]|~SubnetMask.ip[2]);
	ip->ip[3] = (DeviceIP.ip[3]|~SubnetMask.ip[3]);
}


#endif /* PLUNBASE_H_ */
