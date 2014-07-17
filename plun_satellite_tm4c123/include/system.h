/*
 * system.h
 *
 *  Created on: 2014. 7. 16.
 *      Author: Byunghun Hwang <bhhwang@nsynapse.com>
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"

void init_clock()
{
	ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);	//50MHz
}



#endif /* SYSTEM_H_ */
