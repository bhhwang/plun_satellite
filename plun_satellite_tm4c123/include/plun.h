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


#define UART_PORT	0
#define UART_BAUDRATE	115200

enum state { IDLE=0, INIT=1, READY=2, DHCP_CONNECTED=3, PLUN_CONNECTED=4};
enum ledcolor {RED=2, BLUE=4, GREEN=8, OFF=0 };

typedef uint8_t	IPAddress[4];

/*
 * satellite initialization
 */
extern void init_satellite();

/*
 * connect to access point (secure)
 */
extern void connect_ap(char* ssid, const char* pass);

/*
 * disconnect access point
 */
extern void disconnect_ap();

/*
 * getting IP Address
 * Note : you can read address backward. (ex) local[4]= {1,0,168,192}
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
extern unsigned long _isDHCPConfigured();

/*
 * 1 if system is connected to access point
 */
extern unsigned long _isConnectedAP();

/*
 * led indicator (red, green, blue)
 */
extern uint8_t led(uint8_t color);

/*
 * system state (refresh every time tick)
 */
void setState(uint8_t s);


/*
 * MQTT connect
 */
extern bool mqtt_connect(const char* id, IPAddress ip, unsigned int port);

/*
 * MQTT publish
 */
extern bool mqtt_publish(const char* topic, const char* message);



#endif /* PLUN_H_ */
