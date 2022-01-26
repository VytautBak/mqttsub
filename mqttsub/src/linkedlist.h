#ifndef LINKEDLIST
#define LINKEDLIST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "event.h"

struct linked_list {
  struct Node *first;
  struct Node *last;
};

struct Node {
  struct event event;
  struct Node *next;
};

void init_list(struct linked_list *ll);

void add_to_list_end(struct event event, struct linked_list *ll);

void wipe_list(struct linked_list *ll);
#endif
