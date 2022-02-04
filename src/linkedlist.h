#ifndef LINKEDLIST
#define LINKEDLIST
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct linked_list {
  struct Node *first;
  struct Node *last;
};

struct Node {
  void *data;
  struct Node *next;
};

int init_list(struct linked_list *ll);
void add_to_list_end(void *data, struct linked_list *ll);
void wipe_list(struct linked_list *ll, bool free_data);
#endif
