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

#include "include/plun_satellite.h"

enum { IDLE=0 };
static uint8_t cur_state = IDLE;

void setup()
{
	init_satellite();

	wifi_scan();
}

void loop()
{
	switch(cur_state)
	{
	case	IDLE: break;
	}
}

void main(void) {
	
	setup();
	while(1) { loop(); }
}
