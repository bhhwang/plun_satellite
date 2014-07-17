/*
 * uart.h
 *
 *  Created on: 2014. 7. 16.
 *      Author: byunghun
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include <stdbool.h>
#include "utils/uartstdio.h"

/*
 * user definitions
 */
#define USE_UART0
#define UART0_BAUDRATE	115200
#define UART0_PORT	0

void serial_begin(uint32_t port, uint32_t baudrate);


#endif /* UART_H_ */
