/*
 * plun.h
 *
 *  Created on: 2014. 7. 20.
 *      Author: Byunghun Hwang <bhhwang@nsynapse.com>
 */

#ifndef PLUN_H_
#define PLUN_H_

#define SIGNAL_HIGH	0xff
#define SIGNAL_LOW	0x00

#include <stdint.h>
#include <stdbool.h>

#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "driverlib/systick.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"

#include "utils/uartstdio.h"
#include "dispatcher.h"

#include "spi.h"
#include "wlan.h"
#include "evnt_handler.h"
#include "socket.h"
#include "hci.h"
#include "netapp.h"
#include "security.h"

#include "inth.h"

#define UART_PORT	0
#define UART_BAUDRATE	115200

typedef unsigned char	IPAddress[4];
volatile unsigned long isConnectedAP;

void connect_ap(char* ssid, const char* pass)
{
	init_spi(1000000, SysCtlClockGet());	//1MHz SPI
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
void getAddress(IPAddress* local, IPAddress* subnet, IPAddress* gateway, IPAddress* bc)
{
	tNetappIpconfigRetArgs config;
	netapp_ipconfig(&config);

	while(config.aucIP[0]==0){ MAP_SysCtlDelay(10000); }

	local[0] = config.aucIP[3];	//local ip address from dhcp
	local[1] = config.aucIP[2];
	local[2] = config.aucIP[1];
	local[3] = config.aucIP[0];

	subnet[0] = config.aucSubnetMask[3];	//subnet mask
	subnet[1] = config.aucSubnetMask[2];
	subnet[2] = config.aucSubnetMask[1];
	subnet[3] = config.aucSubnetMask[0];

	gateway[0] = config.aucDefaultGateway[3];	//gateway address
	gateway[1] = config.aucDefaultGateway[2];
	gateway[2] = config.aucDefaultGateway[1];
	gateway[3] = config.aucDefaultGateway[0];

	bc[0] = (local[0]|~subnet[0]);	//broadcast
	bc[1] = (local[1]|~subnet[1]);
	bc[2] = (local[2]|~subnet[2]);
	bc[3] = (local[3]|~subnet[3]);
}






#endif /* PLUN_H_ */
