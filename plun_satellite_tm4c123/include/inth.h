/*
 * inth.h
 *
 *  Created on: 2014. 7. 19.
 *      Author: Byunghun Hwang <bhhwang@nsynapse.com>
 */

#ifndef INTH_H_
#define INTH_H_


enum state { IDLE=0, INIT=1, READY=2, DHCP_CONNECTED=3, PLUN_CONNECTED=4};
enum ledcolor {RED=2, BLUE=4, GREEN=8, OFF=0 };


uint8_t led(uint8_t color);
void setState(uint8_t s);


#endif /* INTH_H_ */
