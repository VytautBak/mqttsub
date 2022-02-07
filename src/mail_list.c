#include "mail_list.h"

void init_mail(struct mail *m) {
  m->address = NULL;
  m->next = NULL;  
}