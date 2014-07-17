/*
 * network.h
 *
 *  Created on: 2014. 7. 15.
 *      Author: byunghun
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include "utils/ustdlib.h"

#define DISABLE	0
#define ENABLE	1
extern volatile unsigned long ulSmartConfigFinished, ulCC3000Connected, ulCC3000DHCP, OkToDoShutDown, ulCC3000DHCP_configured, ulCC3000WasConnected;

int DotDecimalDecoder(char *pcString, uint8_t *pui8Val1, uint8_t *pui8Val2, uint8_t *pui8Val3, uint8_t *pui8Val4)
{
    uint32_t ui32Block1, ui32Block2, ui32Block3, ui32Block4;
    char *pcEndData, *pcStartData;

    pcStartData = pcString;
    pcEndData = ustrstr(pcStartData,".");
    ui32Block1 = ustrtoul(pcStartData, 0,10);

    pcStartData = pcEndData +1;
    pcEndData = ustrstr(pcStartData,".");
    ui32Block2 = ustrtoul(pcStartData, 0,10);

    pcStartData = pcEndData +1;
    pcEndData = ustrstr(pcStartData,".");
    ui32Block3 = ustrtoul(pcStartData, 0,10);

    pcStartData = pcEndData +1;
    pcEndData = ustrstr(pcStartData,".");
    ui32Block4 = ustrtoul(pcStartData, 0,10);


    if((ui32Block1 > 255) || (ui32Block2 > 255) || (ui32Block3 > 255) || (ui32Block4 > 255))
        return -1;

    *pui8Val1 = (uint8_t)ui32Block1;
    *pui8Val2 = (uint8_t)ui32Block2;
    *pui8Val3 = (uint8_t)ui32Block3;
    *pui8Val4 = (uint8_t)ui32Block4;

    return 0;
}


typedef struct IPv4 {
	uint8_t ui8IP[4];
	uint32_t ui32IP;
} IPv4;

void convertAddress(IPv4* addr, char* ip)
{
	DotDecimalDecoder(ip, &addr->ui8IP[0], &addr->ui8IP[1], &addr->ui8IP[2], &addr->ui8IP[3]);
	addr->ui32IP = ((addr->ui8IP[0] << 24) + (addr->ui8IP[1] << 16) + (addr->ui8IP[2] << 8 ) + (addr->ui8IP[3] << 0 ));
}

IPv4	g_localAddr, g_netmaskAddr, g_gatewayAddr, g_dnsAddr;



#endif /* NETWORK_H_ */
