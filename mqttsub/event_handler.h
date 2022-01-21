#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uci_handler.h"
#include "text_formatter.h"
#include "event_parser.h"

#define UCI_PATH_LEN 80
#define EVENT_MAX_TOPIC_LEN 30
#define EVENT_MAX_EXPVALUE_LEN 50
#define EVENT_MAX_EMAIL_LEN 100
#define EVENT_MAX_VAR_NAME_LEN 30

enum { EQUAL, NOT_EQUAL, MORE, LESS, MORE_OR_EQUAL, LESS_OR_EQUAL };

struct event {
  uint16_t id;
  char topic[EVENT_MAX_TOPIC_LEN];
  char exp_value[EVENT_MAX_EXPVALUE_LEN];
  char email[EVENT_MAX_EMAIL_LEN];
  int cmp_type;
  bool var_is_num;
  char variable_name[EVENT_MAX_VAR_NAME_LEN];
};

int validate_types(struct event *e, char *value);
int matches_event(struct event *e, char *value);
int event_execute(struct event *e, char *value);
#endif