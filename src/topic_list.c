#include "topic_list.h"

int add_to_topic_list(struct linked_list *topic_list, struct event *event)
{
  struct Node *curr = topic_list->first;
  struct topic *e;

  while (curr->next != NULL) {
    e = curr->data;
    if (strcmp(e->name, event->topic) == 0) {
      add_to_list_end(event, &(e->events));
      return 0;
    }
    curr = curr->next;
  }
  return -1;
}

void add_topic_to_topic_list(struct linked_list *topic_list, char *topic) {
  struct topic *t = malloc(sizeof(struct topic));
  t->name = topic;
  init_list(&(t->events));
  add_to_list_end(t, topic_list);
}