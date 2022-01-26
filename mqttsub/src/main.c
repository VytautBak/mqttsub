#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mosquitto.h"
#include "uci_handler.h"
#include "mosquitto_handler.h"

extern struct linked_list event_list;

int main(int argc, char *argv[])
{
  init_list(&event_list);
  load_events(&event_list);
  struct mosquitto *mosq;
  int rc = create_and_configure_mosq(&mosq, argc, argv);
  if(rc != 0) return rc;


	mosquitto_loop_forever(mosq, 5000, 1);
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();



  return 0;
}
