#ifndef MAIL_LIST_H
#define MAIL_LIST_H

#include <stdio.h>

struct mail {
        char address[512];
        struct mail *next;
};

void init_mail(struct mail *m);
void wipe_mail_list(struct mail *m);

#endif