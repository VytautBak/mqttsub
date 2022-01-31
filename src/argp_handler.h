#include <argp.h>
#include <string.h>
#include "mosquitto.h"
#include "mqtt_config.h"

#ifndef ARGP_HANDLER
#define ARGP_HANDLER



int get_mosq_config(struct config *cfg, int argc, char argv[]);
int client_opts_set(struct mosquitto *mosq, struct config *cfg);
#endif


