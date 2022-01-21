#include <uci.h>
#include "event_handler.h"
#include "mail.h"

#ifndef UCI_HANDLER_H
#define UCI_HANDLER_H
#define CONFIG_NAME "mqttsub"


int match_event(char *topic, char *value);
int proccess_message(char *topic, char *value);


#endif