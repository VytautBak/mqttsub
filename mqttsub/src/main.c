#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mosquitto.h"
#include "mosquitto_handler.h"
#include "uci_handler.h"
#include "event.h"
#include "sig_action_handler.h"

void cleanup(struct mosquitto *mosq, struct linked_list *ll)
{
  if(mosq != NULL) mosquitto_destroy(mosq);
  mosquitto_lib_cleanup();
  wipe_list(ll);
//  dealloc_list(ll);
// check if this works
}

int main(int argc, char *argv[])
{
  int rc;

  struct linked_list event_list;
  rc = init_list(&event_list);
  if (rc != 0) {
    return rc;
  }

  rc = load_events(&event_list);
  if (rc != 0) {
    wipe_list(&event_list);
    dealloc_list(&event_list);
    return rc;
  }

  struct mosquitto *mosq = NULL;
  struct config cfg;

  cfg.event_list = &event_list;

  
  rc = create_and_configure_mosq(&mosq, &cfg, argc, argv);
  if (rc != 0) {
    cleanup(mosq, &event_list);
    return rc;
  }
  setup_sig_action(mosq, &cfg);

  fprintf(stdout, "INFO: Succesfully connected to MQTT server\n");
  rc = mosquitto_loop_forever(mosq, 5000, 1);
  if (rc != 0) {
    fprintf(stderr, "ERROR: %s\n", mosquitto_strerror(rc));
  }

  cleanup(mosq, &event_list);
  return 0;
}
