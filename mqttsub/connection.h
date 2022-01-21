
#include "mosquitto.h"
#include <stdio.h>
#include "client_shared.h"
#include <assert.h>
#include "event_handler.h"
#include "uci_handler.h"
#ifndef CONNECTION_H
#define CONNECTION_H

void my_message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message);
void my_connect_callback(struct mosquitto *mosq, void *obj, int result);
void my_subscribe_callback(struct mosquitto *mosq, void *obj, int mid, int qos_count, const int *granted_qos);
//void my_log_callback(struct mosquitto *mosq, void *obj, int level, const char *str)
void message_check_for_events(char *topic, char *message);
void my_log_callback(struct mosquitto *mosq, void *obj, int level, const char *str);

#endif