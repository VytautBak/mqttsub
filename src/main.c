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

int main(int argc, char *argv[])
{
  if (is_only_instance() != 0) return -1;
/*
  // for debug purposes
  char *newargv[] = {"mqttsub",
                     "-h",
                     "192.168.1.1",
                     "-u",
                     "admin",
                     "-P",
                     "admin",
                     "--cafile",
                     "/home/studentas/Desktop/ca.cert.pem",
                     "-p",
                     "8883",
                     "--save",
                     "-t",
                     "testing/testing",
                     "-t",
                     "abd"};
  int newargc = 16;
  int rc;*/

  struct mosquitto *mosq = NULL;
  struct config cfg;

  topic_list = malloc(sizeof(struct topic));
  if(topic_list == NULL) {
    goto cleanup;
  }

  init_topic(topic_list);

  int rc = create_and_configure_mosq(&mosq, &cfg, argc, argv);
  if (rc != 0) {
    goto cleanup;
  }

  rc = load_events(topic_list);
  if (rc != 0) {
    goto cleanup;
  }

  setup_sig_action(mosq);
  rc = mosquitto_loop_forever(mosq, 5000, 1);
  if (rc != 0) {
    fprintf(stderr, "ERROR: %s\n", mosquitto_strerror(rc));
  }

cleanup:
  wipe_topic_list(topic_list);
  if (mosq != NULL) mosquitto_destroy(mosq);
  mosquitto_lib_cleanup();
  
  return rc;
}
