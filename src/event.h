
#ifndef EVENT_H
#define EVENT_H
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"
#define EVENT_MAX_TOPIC_LEN 256
#define EVENT_MAX_EXPVALUE_LEN 256
#define EVENT_MAX_EMAIL_LEN 256
#define EVENT_MAX_VAR_NAME_LEN 256
#define MAX_NUM_OF_EMAILS 10

struct topic {
  struct linked_list *list;
  char *name;
};

struct event {
  uint16_t id;
  char topic[EVENT_MAX_TOPIC_LEN];
  char exp_value[EVENT_MAX_EXPVALUE_LEN];
  char email[MAX_NUM_OF_EMAILS][EVENT_MAX_EMAIL_LEN];
  int num_of_emails;
  int cmp_type;
  bool var_is_num;
  char variable_name[EVENT_MAX_VAR_NAME_LEN];
};

#endif