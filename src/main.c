#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "event.h"
#include "file_locker.h"
#include "mosquitto.h"
#include "mosquitto_handler.h"
#include "sig_action_handler.h"
#include "topic_list.h"
#include "uci_handler.h"

struct topic *topic_list;

void cleanup(struct mosquitto *mosq, struct linked_list *ll)
{
  /*
  if (mosq != NULL) mosquitto_destroy(mosq);
  mosquitto_lib_cleanup();

  struct topic *t;
  struct Node *tcurr = ll->first;
  while (tcurr != NULL) {
    t = tcurr->data;
    struct Node *ecurr = t->events.first;
    while (ecurr != NULL) {
      struct event *e = ecurr->data;
      wipe_list(&(e->receiver_emails), true);

      ecurr = ecurr->next;
    }
    wipe_list(&(t->events), false);


    tcurr = tcurr->next;
  }
  wipe_list(ll, true);*/

}

int main(int argc, char *argv[])
{
 // if (is_only_instance() != 0) return -1;

  //for debug purposes
  char *newargv[] = {"mqttsub", "-h", "192.168.1.1", "-u", "admin", "-P", "admin", "--cafile", "/home/studentas/Desktop/ca.cert.pem", "-p", "8883", "--save", "-t", "testing/testing", "-t", "abd"};
  int newargc = 16;
  int rc;

  struct mosquitto *mosq = NULL;
  struct config cfg;

  topic_list = malloc(sizeof(struct topic));
  /* Init topic_list linkedlist */

  init_topic(topic_list);

  
  rc = create_and_configure_mosq(&mosq, &cfg, newargc, newargv);
  if (rc != 0) {
    cleanup(mosq, &topic_list);
    return rc;
  }
  

  rc = load_events(topic_list);
  if (rc != 0) {
   // wipe_list(&topic_list, false);
    return rc;
  }
  
   setup_sig_action(mosq);
  rc = mosquitto_loop_forever(mosq, 5000, 1);
  if (rc != 0) {
    fprintf(stderr, "ERROR: %s\n", mosquitto_strerror(rc));
  }


  //cleanup(mosq, &topic_list);*/
  return 0;
}
