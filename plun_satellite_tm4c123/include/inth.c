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


#define SYSTICK_PER_SECOND	10
void SysTickHandler(void)
{
    //static unsigned long ulTickCount = 0;
    static uint8_t	data = 2;

    MAP_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, data);
	if(data==2) data=0; else data=2;
}




#endif /* INTH_C_ */
