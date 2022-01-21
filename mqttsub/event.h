
#ifndef EVENT_H
#define EVENT_H
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define EVENT_MAX_TOPIC_LEN 30
#define EVENT_MAX_EXPVALUE_LEN 50
#define EVENT_MAX_EMAIL_LEN 100
#define EVENT_MAX_VAR_NAME_LEN 30

struct event {
  uint16_t id;
  char topic[EVENT_MAX_TOPIC_LEN];
  char exp_value[EVENT_MAX_EXPVALUE_LEN];
  char email[EVENT_MAX_EMAIL_LEN];
  int cmp_type;
  bool var_is_num;
  char variable_name[EVENT_MAX_VAR_NAME_LEN];
};






#endif