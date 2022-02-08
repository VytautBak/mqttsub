#include "event.h"

void wipe_event_list(struct event *e)
{
  struct event *tmp;
  while (e != NULL) {
    tmp = e;
    wipe_mail_list(e->receiver_address);
    e = e->next;
    free(tmp);
  }
}