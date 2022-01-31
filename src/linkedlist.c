#include "linkedlist.h"

int init_list(struct linked_list *ll)
{
  ll->first = malloc(sizeof(struct Node));
  if (ll->first == NULL) {
    fprintf(stderr, "ERROR: Could not allocate memory for list\n");
    return -1;
  }
  ll->last = malloc(sizeof(struct Node));
  if (ll->last == NULL) {
    fprintf(stderr, "ERROR: Could not allocate memory for list\n");
    return -1;
  }
  ll->first->next = ll->last;
  return 0;
}

void add_to_list_end(struct event event, struct linked_list *ll)
{
  struct Node *curr = ll->first;
  while (curr->next != ll->last) {
    curr = curr->next;
  }
  curr->next = malloc(sizeof(struct Node));
  curr->next->event = event;
  curr->next->next = ll->last;
}

void wipe_list(struct linked_list *ll)
{
  struct Node *curr = ll->first->next;
  while (curr->next != ll->last) {
    struct Node *tmp = curr;
    curr = curr->next;
    free(tmp);
  }
  ll->first->next = ll->last;
}

void dealloc_list(struct linked_list *ll) {
  free(ll->first);
  free(ll->last);
  free(ll);
}
