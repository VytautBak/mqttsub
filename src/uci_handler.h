#include <uci.h>
#include "event_handler.h"
#include "mail.h"
#include "linkedlist.h"
#include <string.h>

#ifndef UCI_HANDLER_H
#define UCI_HANDLER_H
#define CONFIG_NAME "mqttsub"


int load_events(struct linked_list *list);

#endif