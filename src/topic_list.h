#include "linkedlist.h"
#include "event.h"
#include <string.h>
#include <stdbool.h>
#ifndef TOPIC_LIST_H
#define TOPIC_LIST_H

struct topic {
  char *name;
  struct linked_list events;
};

int add_to_topic_list(struct linked_list *topic_list, struct event *event);
void add_topic_to_topic_list(struct linked_list *topic_list, char *topic);
#endif