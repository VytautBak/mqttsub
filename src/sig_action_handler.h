#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include "mosquitto.h"
#include "mosquitto_handler.h"
#ifndef SIG_ACTION_HANDLER_H
#define SIG_ACTION_HANDLER_H

void setup_sig_action(struct mosquitto *obj, struct config *cfg);
void reload_proc(int sigterm);
void term_proc(int sigterm);

#endif