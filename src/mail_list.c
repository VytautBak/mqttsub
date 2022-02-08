#include "mail_list.h"

void init_mail(struct mail *m) {
  m->next = NULL;  
}

void wipe_mail_list(struct mail *m) {
  struct mail *tmp;
  while(m != NULL) {
    tmp = m;
    m = m->next;
    free(tmp);
  }
}