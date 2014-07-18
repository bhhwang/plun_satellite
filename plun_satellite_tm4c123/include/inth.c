/*
 * inth.c
 *
 *  Created on: 2014. 7. 18.
 *      Author: Byunghun Hwang <bhhwang@nsynapse.com>
 *      Desc. : Interrupt Service Handler.
 *      Note : Check tm4c123gh6pm_startup_css.c file, if you want to edit
 */

#ifndef INTH_C_
#define INTH_C_

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/pin_map.h"
#include "driverlib/rom_map.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"

/*
 * background worker for PLUN like state indicator
 */
enum state { IDLE=0, READY=1 };
enum ledcolor {RED=2, BLUE=4, GREEN=8, OFF=0 };
static uint32_t	state = IDLE;

uint8_t led(uint8_t color) { MAP_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, color); return color; }
void led_blink(uint8_t color)
{
	static uint8_t prev = OFF;
	if(prev==OFF) prev=led(color);
	else prev=led(OFF);
}
void setState(uint8_t s){ state = s; }
void PlunWorker(void)
{
    switch(state)
    {
    case	IDLE:
    	led_blink(BLUE);
    	break;
    case	READY:
    	//led_blink(RED);
    	break;
    }
}




#endif /* INTH_C_ */
