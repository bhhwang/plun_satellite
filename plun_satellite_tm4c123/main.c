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

IPAddress locali, gateway, subnet, broadcast;

void main(void)
{
	init_satellite();

	connect_ap(ssid, pass);
	while(1)
	{
		getLocalIP(&localip);
		getGateway(&gateway);
		getSubnetMask(&subnet);
		getBroadcast(&broadcast);
		if(localip.ip[3]!=0)	break;
	}

	UARTprintf("\nIP : %d.%d.%d.%d",localip.ip[0],localip.ip[1],localip.ip[2],localip.ip[3]);
	UARTprintf("\nGateway : %d.%d.%d.%d",gateway.ip[0],gateway.ip[1],gateway.ip[2],gateway.ip[3]);
	UARTprintf("\nSubnet Mask : %d.%d.%d.%d",subnet.ip[0],subnet.ip[1],subnet.ip[2],subnet.ip[3]);
	UARTprintf("\nBroadcast : %d.%d.%d.%d",broadcast.ip[0],broadcast.ip[1],broadcast.ip[2],broadcast.ip[3]);

	while(1) {}
}
