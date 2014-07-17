/*
 * param_setup.h
 *
 *  Created on: 2014. 7. 15.
 *      Author: Byunghun Hwang <bhhwang@nsynapse.com>
 */

#ifndef PARAM_SETUP_H_
#define PARAM_SETUP_H_



#define USE_UART0	//if do not want, comment this line
#define USE_CC3000	//if do not want, comment this line



/*
 * UART setting
 */
#ifdef USE_UART0
#define UART0_BAUDRATE	115200
#define UART0_PORT	0
#endif

/*
 * CC3000 setting
 */
#ifdef USE_CC3000
#include "wlan.h"
#include "evnt_handler.h"
#include "nvmem.h"
#include "cc3000_common.h"
#include "netapp.h"
#include "spi.h"
#include "hci.h"
#include "spi_version.h"
#include "board.h"
#include "host_driver_version.h"
#include "security.h"
#include "network.h"

const char ssid[] = "nsynapse";
const char pass[] = "ghkdqudgns";

#endif



#endif /* PARAM_SETUP_H_ */
