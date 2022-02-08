
#ifndef EVENT_H
#define EVENT_H
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "mail_list.h"
#define EVENT_MAX_TOPIC_LEN 256
#define EVENT_MAX_EXPVALUE_LEN 256
#define EVENT_MAX_EMAIL_LEN 256
#define EVENT_MAX_VAR_NAME_LEN 50
#define MAX_URL_LEN 256
#define SMTP_MAX_USERNAME_LEN 256
#define SMTP_MAX_PASSWORD_LEN 256



struct event {
  uint16_t id;
  char topic[EVENT_MAX_TOPIC_LEN];
  char exp_value[EVENT_MAX_EXPVALUE_LEN];

  int cmp_type;
  bool var_is_num;
  char variable_name[EVENT_MAX_VAR_NAME_LEN];


  struct mail *receiver_address;
  char sender_email[EVENT_MAX_EMAIL_LEN];


  char smtp_url[MAX_URL_LEN];
  char smtp_username[SMTP_MAX_USERNAME_LEN];
  char smtp_password[SMTP_MAX_PASSWORD_LEN];

  struct event *next;
};
void wipe_event_list(struct event *e);

#endif