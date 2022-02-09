
#include <errno.h>
#include <stdio.h>

#include "argp_handler.h"
#include "event_handler.h"
#include "file_writer.h"
#include <mosquitto.h>
#include "mqtt_config.h"
#ifndef MOSQUITTO_HANDLER_H
#define MOSQUITTO_HANDLER_H

int create_and_configure_mosq(struct mosquitto **mosq, struct config *cfg, int argc, char argv[]);
struct mosquitto *create_mosq(struct config *cfg);
int mosq_connect(struct mosquitto *mosq, struct config *cfg);
int configure_mosq(struct mosquitto *mosq, struct config *cfg);
void mosq_connect_cb(struct mosquitto *mosq, void *obj, int result);
void init_config(struct config *cfg);
int reload_config(struct config *cfg);
#endif