#ifndef MAIL_LIST_H
#define MAIL_LIST_H

#include <stdio.h>


struct mail {
  char *address;
  struct mail *next;
};

void init_mail(struct mail *m);

#endif