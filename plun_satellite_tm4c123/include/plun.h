/*
 * plun.h
 *
 *  Created on: 2014. 7. 20.
 *      Author: Byunghun Hwang <bhhwang@nsynapse.com>
 */

#ifndef PLUN_H_
#define PLUN_H_

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
#include "socket.h"

#define SIGNAL_HIGH	0xff
#define SIGNAL_LOW	0x00

#define UART_PORT	0
#define UART_BAUDRATE	115200

enum state {
	IDLE = 0,	//nothing to do.
	INIT = 1,	//initial state
	READY = 2, 	//after initialized, waiting for any input signal
	AP_CONNECTED = 3,	//getting ip address & trying to connect plun host
	HOST_CONNECTED = 4	//connected to host
};
enum ledcolor {RED=2, BLUE=4, GREEN=8, OFF=0 };

typedef uint8_t	IPAddress[4];

/*
 * satellite initialization
 */
extern void init_satellite_tm4c();
extern void connect_ap(char* ssid, const char* pass);
extern void disconnect_ap();

/*
 * getting IP Address
 * Note : you should read address backward. (ex) local[4]= {1,0,168,192}
 */
extern void getAddress(IPAddress* local, IPAddress* subnet, IPAddress* gateway, IPAddress* bc);

/*
 * for Wifi interrupt handler and so on..
 */
extern void CC3000_AsyncCallback(long lEventType, char *data, unsigned char length);
extern char* sendDriverPatch(unsigned long *Length);
extern char* sendBootLoaderPatch(unsigned long *Length);
extern char* sendWLFWPatch(unsigned long *Length);
extern long ReadWlanInterruptPin(void);
extern void WlanInterruptEnable();
extern void WlanInterruptDisable();
extern void WriteWlanPin(unsigned char val);


/*
 * 1 if system got dynamic IP address from HDCP
 */
extern unsigned long is_dhcp_configured();
extern unsigned long is_connected_ap();

extern uint8_t led(uint8_t color);

void setState(uint8_t s);


/*
 * mqtt functions
 */
extern bool mqtt_connect(const char* id, IPAddress ip, unsigned int port);
extern bool mqtt_publish(const char* topic, const char* message);



#endif /* PLUN_H_ */
