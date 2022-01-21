#include <assert.h>
#include <errno.h>
#include "mosquitto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "client_shared.h"
#include "connection.h"


int main(int argc, char *argv[])
{
  struct mosq_config cfg;
  struct mosquitto *mosq = NULL;
  int rc;

  rc = client_config_load(&cfg, CLIENT_SUB, argc, argv);
  if (rc) {
    client_config_cleanup(&cfg);
    if (rc == 2) {
      /* --help */
      print_usage();
    } else {
      fprintf(stderr, "\nUse 'mosquitto_sub --help' to see usage.\n");
    }
    return 1;
  }

  mosquitto_lib_init();

  if (client_id_generate(&cfg, "mosqsub")) {
    return 1;
  }

  mosq = mosquitto_new(cfg.id, cfg.clean_session, &cfg);
  if (!mosq) {
    switch (errno) {
      case ENOMEM:
        if (!cfg.quiet) fprintf(stderr, "Error: Out of memory.\n");
        break;
      case EINVAL:
        if (!cfg.quiet)
          fprintf(stderr,
                  "Error: Invalid id and/or "
                  "clean_session.\n");
        break;
    }
    mosquitto_lib_cleanup();
    return 1;
  }
  if (client_opts_set(mosq, &cfg)) {
    return 1;
  }
  if (cfg.debug) {
    mosquitto_log_callback_set(mosq, my_log_callback);
    mosquitto_subscribe_callback_set(mosq, my_subscribe_callback);
  }
  mosquitto_connect_callback_set(mosq, my_connect_callback);
  mosquitto_message_callback_set(mosq, my_message_callback);

  rc = client_connect(mosq, &cfg);
  if (rc) return rc;

  rc = mosquitto_loop_forever(mosq, -1, 1);

  mosquitto_destroy(mosq);
  mosquitto_lib_cleanup();

  if (cfg.msg_count > 0 && rc == MOSQ_ERR_NO_CONN) {
    rc = 0;
  }
  if (rc) {
    fprintf(stderr, "Error: %s\n", mosquitto_strerror(rc));
  }
  return rc;
}
