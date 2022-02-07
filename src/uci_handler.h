#include <uci.h>
//#include "event_handler.h"
#include "mail.h"
#include "linkedlist.h"
#include <string.h>
#include "event.h"
#include "topic_list.h"
#ifndef UCI_HANDLER_H
#define UCI_HANDLER_H
#define CONFIG_NAME "mqttsub"


int load_events(struct topic *topic_list);

#endif