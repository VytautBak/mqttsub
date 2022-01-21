#include <uci.h>


#ifndef UCI_HANDLER_H
#define UCI_HANDLER_H
#include "event_handler.h"
#include "mail.h"
#define CONFIG_NAME "mqttsub"


int match_event(char *topic, char *value);
int proccess_message(char *topic, char *value);


#endif