#include <string.h>
#include <uci.h>

#include "event.h"
#include "mail.h"
#include "mail_list.h"
#include "topic_list.h"
#ifndef UCI_HANDLER_H
#define UCI_HANDLER_H
#define CONFIG_NAME "mqttsub"

int load_events(struct topic *topic_list);
int parse_section(struct uci_section *section, struct event *event);
#endif