#include "topic_list.h"

int add_to_topic_list(struct topic *topic_list, struct event *event) {
        struct topic *currt = topic_list;

        while (currt != NULL) {
                if (strcmp(currt->name, event->topic) == 0) {
                        if (currt->event_list == NULL) {
                                currt->event_list = event;
                                return 0;
                        } else {
                                event->next = currt->event_list;
                                currt->event_list = event;
                                return 0;
                        }
                }
                currt = currt->next;
        }

        return -1;
}

void add_topic_to_topic_list(struct topic **topic_list, char *topic) {
        if ((*topic_list)->name == NULL) {
                (*topic_list)->name = topic;
        } else {
                struct topic *t = malloc(sizeof(struct topic));
                t->event_list = NULL;
                t->name = topic;
                t->next = *topic_list;
                *topic_list = t;
        }
}

void init_topic(struct topic *t) {
        t->event_list = NULL;
        t->name = NULL;
        t->next = NULL;
}

void wipe_topic_list(struct topic *t) {
        struct topic *tmp;
        while (t != NULL) {
                wipe_event_list(t->event_list);
                tmp = t;
                t = t->next;
                free(tmp);
        }
}
