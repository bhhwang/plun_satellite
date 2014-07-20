/*
 * plun satellite (TI TM4C123G) firmware for TI's TM4C123GH6PM Launchpad
 * programmed by Byunghun Hwang <bhhwang@nsynapse.com>
 * Copyright (c) Nsynapse Inc. All rights reserved.
 * Version : 0.0.1
 * Date : 2014. 7. 14
 *
 * Note : This firmware can be used for TI's TM4C123GH6PM Launchpad with CC3000 WiFi boostpack.
 * 		  We hope to re-configure all code for fast implementation, but all functions will not support.
 */

#include "include/plun.h"

char ssid[] = "nsynapse";
char pass[] = "ghkdqudgns";

IPAddress local, gateway, subnet, broadcast;

void main(void)
{
	init_satellite();

	UARTprintf("PLUN Satellite\n");
	connect_ap(ssid, pass);

	while(!(_isConnectedAP() && _isDHCPConfigured()))
		MAP_SysCtlDelay(1000000);

	getAddress(&local, &gateway, &subnet, &broadcast);

	UARTprintf("Local IP : %d.%d.%d.%d\n",local[3],local[2],local[1],local[0]);
	UARTprintf("Gateway IP : %d.%d.%d.%d\n",gateway[3],gateway[2],gateway[1],gateway[0]);
	UARTprintf("Subnet IP : %d.%d.%d.%d\n",subnet[3],subnet[2],subnet[1],subnet[0]);
	UARTprintf("Broadcast IP : %d.%d.%d.%d\n",broadcast[3],broadcast[2],broadcast[1],broadcast[0]);

	while(1) { MAP_SysCtlDelay(1000); };

}
