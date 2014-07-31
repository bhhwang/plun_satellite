/*
 * PLUN Satellite TM4C ver 0.0.1
 *      Author: Byunghun Hwang <bhhwang@nsynapse.com>
 * History
 */

#include "plun.h"

//SSID and PASS will remove after
char ssid[] = "nsynapse"
char pass[] = "ghkdqudgns"

int main(void) {
	
	//1. board initialize
	init_satellite();

	//2. setup
	setup_wifi(ssid, pass);
	setup_uart(115200);

	return 0;
}
