#include <argp.h>
#include <string.h>
#include "mosquitto.h"
#include "mqtt_config.h"
#include <unistd.h>

#ifndef ARGP_HANDLER
#define ARGP_HANDLER

static error_t parse_opt(int key, char *arg, struct argp_state *state);
int get_mosq_config(struct config *cfg, int argc, char argv[]);
int argp_validate(struct config *cfg);
int validate_topic(char *topic);
#endif


