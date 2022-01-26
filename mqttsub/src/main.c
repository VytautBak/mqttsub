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
  fprintf(stdout, "STARTED PROGRAM");
  init_list(&event_list);
  load_events(&event_list);
  struct mosquitto *mosq;
  printf("loaded events\n");
  int rc = create_and_configure_mosq(&mosq, argc, argv);
  printf("congifured mosq\n");
  if(rc != 0) printf("rc = %d\n", rc);


	mosquitto_loop_forever(mosq, 5000, 1);
    printf("looping forever\n rc = %d \n", rc);
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();



  return 0;
}
