#include "linkedlist.h"

int init_list(struct linked_list *ll)
{
  ll->first = NULL;
  return 0;
}

void add_to_list_end(void *data, struct linked_list *ll)
{
/*ADD CHECK INCASE MALLOC FAILS*/

  if (ll->first == NULL) {
    ll->first = malloc(sizeof(struct Node));
    ll->first->next = NULL;
    ll->first->data = data;
    return;
  } else {
    struct Node *tmp = malloc(sizeof(struct Node));
    tmp->data = data;
    tmp->next = ll->first;
    ll->first = tmp;
  }
}

void wipe_list(struct linked_list *ll, bool free_data)
{
  struct Node *curr = ll->first;
  struct Node *tmp;
  while (curr != NULL) {
    tmp = curr;
    curr = curr->next;
    if (free_data == 1) free(tmp->data);
    free(tmp);
  }
}
