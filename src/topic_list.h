#include "linkedlist.h"
#include "event.h"
#include <string.h>
#include <stdbool.h>
#ifndef TOPIC_LIST_H
#define TOPIC_LIST_H

struct topic {
  char *name;
  struct event *event_list;
  struct topic *next;
};

int add_to_topic_list(struct topic *topic_list, struct event *event);
void init_topic(struct topic *t);
void add_topic_to_topic_list(struct topic **topic_list, char *topic);
#endif