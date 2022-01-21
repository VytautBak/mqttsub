#include "event.h"


int validate_event(struct event *e) {


}


int clean_event(struct event *e) {
  e->id = 0;
  memset(e->topic, "+", EVENT_MAX_TOPIC_LEN); /*Setting this to "+++.." is so we can later check if topic has been set ('+' cannot exist in valid topic name)*/
  e->exp_value = NULL;




}
