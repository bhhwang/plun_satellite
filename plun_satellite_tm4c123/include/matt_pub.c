/*
 * matt_pub.c
 *
 *  Created on: 2014. 7. 20.
 *      Author: Byunghun Hwang <bhhwang@nsynapse.com>
 *
 *      modified from open source code ( ? )
 */

#include "plun.h"


#define MQTT_MAX_PACKET_SIZE	256
#define MQTT_KEEPALIVE	14400 	///keepalive interval in seconds

#define MQTTPROTOCOLVERSION 3
#define MQTTCONNECT 		1 << 4 // Client request to connect to Server
#define MQTTCONNACK 		2 << 4 // Connect Acknowledgment
#define MQTTPUBLISH 		3 << 4 // Publish message
#define MQTTPUBACK 			4 << 4 // Publish Acknowledgment
#define MQTTPUBREC 			5 << 4 // Publish Received (assured delivery part 1)
#define MQTTPUBREL 			6 << 4 // Publish Release (assured delivery part 2)
#define MQTTPUBCOMP 		7 << 4 // Publish Complete (assured delivery part 3)
#define MQTTSUBSCRIBE 		8 << 4 // Client Subscribe request
#define MQTTSUBACK 			9 << 4 // Subscribe Acknowledgment
#define MQTTUNSUBSCRIBE 	10 << 4 // Client Unsubscribe request
#define MQTTUNSUBACK 		11 << 4 // Unsubscribe Acknowledgment
#define MQTTPINGREQ 		12 << 4 // PING Request
#define MQTTPINGRESP 		13 << 4 // PING Response
#define MQTTDISCONNECT 		14 << 4 // Client is Disconnecting
#define MQTTRESERVED 		15 << 4 // Reserved

#define MQTTQOS0 (0 << 1)
#define MQTTQOS1 (1 << 1)
#define MQTTQOS2 (2 << 1)


bool mqtt_connect(const char* id, IPAddress ip, unsigned int port)
{
	return true;
}

bool mqtt_disconnect()
{

}


bool mqtt_publish(const char* topic, const char* message)
{
	return true;
}

