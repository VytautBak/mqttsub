#ifndef TEXT_FORMATTER_H
#define TEXT_FORMATTER_H

#include "event_handler.h"


void get_formatted_time(char *string);
void get_formatted_payload(char *payload, char *details);
void get_formatted_details(char *details, struct event *e, char *value);



#endif