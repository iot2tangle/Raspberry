#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <stdbool.h>
#include "mqtt.h"
#include "MQTTClient.h"

char p_str[10];
char address[40];

MQTTClient client;
MQTTClient_deliveryToken token;
int rc;
int QOS;

bool socket_sender(const char* endp, int p, const char* top, const char* us, const char* pass, char* j, long t)
{
	QOS = 1;
	sprintf(p_str, "%d", p);	/* Convert port to string */
	
	strcpy(address, "tcp://");
    strcat(address, endp);
    strcat(address, ":");    
    strcat(address, p_str);
    
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;

    MQTTClient_create(&client, address, us, MQTTCLIENT_PERSISTENCE_NONE, NULL);

    // MQTT Connection parameters
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.username = us;
    conn_opts.password = pass;


    if ((rc = MQTTClient_connect(client, &conn_opts)) == MQTTCLIENT_SUCCESS)
	{
		// Publish message
		pubmsg.payload = j;
		pubmsg.payloadlen = strlen(j);
		pubmsg.qos = QOS;
		pubmsg.retained = 0;
		MQTTClient_publishMessage(client, top, &pubmsg, &token);

		rc = MQTTClient_waitForCompletion(client, token, t*1000);

		// Disconnect
		MQTTClient_disconnect(client, t*1000);
		MQTTClient_destroy(&client);
    }
    
    printf("			*** ");
    if (rc == 0)	
		{
			printf("Data Published in the Broker!\n");
			return true;
		} 
    else
    {
		if (rc==1)
	        printf("Connection refused: Unacceptable protocol version\n");
		if (rc==2)
	        printf("Connection refused: Identifier rejected\n");
		if (rc==3)
	        printf("Connection refused: Server unavailable\n");
		if (rc==4)
	        printf("Connection refused: Bad user name or password\n");
		if (rc==5)
	        printf("Connection refused: Not authorized\n");	 
	    else  
	        printf("Connection failed\n");    
	    
	    return false;
    }
}

bool init_socket(const char* endp, int p, const char* us, const char* pass, bool _ft_http)
{
	QOS = 1;
	sprintf(p_str, "%d", p);	/* Convert port to string */
	
	strcpy(address, "tcp://");
    strcat(address, endp);
    strcat(address, ":");    
    strcat(address, p_str);
    
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;

    MQTTClient_create(&client, address, us, MQTTCLIENT_PERSISTENCE_NONE, NULL);

    // MQTT Connection parameters
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.username = us;
    conn_opts.password = pass;

    rc = MQTTClient_connect(client, &conn_opts);
    if (rc == 0)	
		{
			printf(" -- The Configuration Network is correct, sending data to The Tangle --\n");
			return true;
		} 
    else
    {
		if (rc==1)
	        printf(" -- MQTT Connection refused: Unacceptable protocol version --\n");
		if (rc==2)
	        printf(" -- MQTT Connection refused: Identifier rejected --\n");
		if (rc==3)
	        printf(" -- MQTT Connection refused: Server unavailable --\n");
		if (rc==4)
	        printf(" -- MQTT Connection refused: Bad user name or password --\n");
		if (rc==5)
	        printf(" -- MQTT Connection refused: Not authorized --\n");	 
	    else  
	        printf(" -- MQTT Connection failed --\n");    
	    
	    return false;
    }  
}


