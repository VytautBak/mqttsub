#include <uci.h>
#include "mail.h"
#include <string.h>
#include "event.h"
#include "topic_list.h"
#include "mail_list.h"
#ifndef UCI_HANDLER_H
#define UCI_HANDLER_H
#define CONFIG_NAME "mqttsub"


int load_events(struct topic *topic_list);

#endif