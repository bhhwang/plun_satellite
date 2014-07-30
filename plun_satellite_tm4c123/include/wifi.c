
#ifndef WIFI_C_
#define WIFI_C_

#include "plun.h"
#include "socket.h"

#define NETAPP_IPCONFIG_MAC_OFFSET	20

volatile unsigned long connected_ap;
volatile unsigned long ulSmartConfigFinished,cc3000_dhcp, OkToDoShutDown, ulCC3000WasConnected;

/*
 * defined functions
 */
unsigned long is_dhcp_configured() { return cc3000_dhcp; }
unsigned long is_connected_ap() { return connected_ap; }
bool connect_plun_host();

/*
 * function impl.
 */
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

	while(connected_ap==0)	{ MAP_SysCtlDelay(10000); }	//wait until connecting

	setState(AP_CONNECTED);
}

void disconnect_ap()
{
	wlan_disconnect();
}

void getAddress(IPAddress* local, IPAddress* subnet, IPAddress* gateway, IPAddress* bc)
{
	tNetappIpconfigRetArgs config;
	netapp_ipconfig(&config);

	memcpy(local, config.aucIP, sizeof(config.aucIP));
	memcpy(subnet, config.aucSubnetMask, sizeof(config.aucSubnetMask));
	memcpy(gateway, config.aucIP, sizeof(config.aucDefaultGateway));

	unsigned char _bc[4];
	_bc[3] = config.aucIP[3]|~config.aucSubnetMask[3];
	_bc[2] = config.aucIP[2]|~config.aucSubnetMask[2];
	_bc[1] = config.aucIP[1]|~config.aucSubnetMask[1];
	_bc[0] = config.aucIP[0]|~config.aucSubnetMask[0];

	memcpy(bc, _bc, sizeof(_bc));
}

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

void CC3000_AsyncCallback(long lEventType, char *data, unsigned char length)
{

	if (lEventType == HCI_EVNT_WLAN_ASYNC_SIMPLE_CONFIG_DONE)
		ulSmartConfigFinished = 1;

	if (lEventType == HCI_EVNT_WLAN_UNSOL_CONNECT)
		connected_ap = 1;

	if (lEventType == HCI_EVNT_WLAN_UNSOL_DISCONNECT)
	{
		connected_ap = 0;
		cc3000_dhcp = 0;
	}

	if (lEventType == HCI_EVNT_WLAN_UNSOL_DHCP)
	{
		if ( *(data + NETAPP_IPCONFIG_MAC_OFFSET) == 0)
			cc3000_dhcp = 1;
		else
			cc3000_dhcp = 0;
	}

	if (lEventType == HCI_EVENT_CC3000_CAN_SHUT_DOWN)
		OkToDoShutDown = 1;
}

long ReadWlanInterruptPin(void){ return MAP_GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_2); }
void WlanInterruptEnable(){ MAP_GPIOIntEnable(GPIO_PORTB_BASE, GPIO_PIN_2); }
void WlanInterruptDisable(){ MAP_GPIOIntDisable(GPIO_PORTB_BASE, GPIO_PIN_2); }
void WriteWlanPin( unsigned char val ){ val?MAP_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, SIGNAL_HIGH):MAP_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, SIGNAL_LOW); }




#endif
