

#ifndef EVENT_PARSER_H
#define EVENT_PARSER_H
#include "event_handler.h"
#include "uci.h"
int event_parse_option(struct event *e, char *option, char *value);
int event_parse_emails(struct event *e, struct uci_list *list, char *option);
#endif