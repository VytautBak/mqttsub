#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uci_handler.h"
#include "text_formatter.h"
#include "event_parser.h"
#include "event.h"

enum { EQUAL, NOT_EQUAL, MORE, LESS, MORE_OR_EQUAL, LESS_OR_EQUAL };

int validate_types(struct event *e, char *value);
int matches_event(struct event *e, char *value);
int event_execute(struct event *e, char *value);
#endif