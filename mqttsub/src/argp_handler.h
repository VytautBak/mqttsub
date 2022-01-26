#include <argp.h>
#include <string.h>
#include "mosquitto.h"

#ifndef ARGP_HANDLER
#define ARGP_HANDLER

#define MAX_TOPIC_LENGTH 100
#define MAX_NUM_OF_TOPICS 10

struct config {
  char *host;
  char *port;
  char *cert;
  char *topics[MAX_NUM_OF_TOPICS];
  char *username;
  char *password;
  char *keepalive;
  int max_inflight;
  int protocol_version;
  __uint16_t num_of_topics;
};

int get_mosq_config(struct config *cfg, int argc, char argv[]);
int client_opts_set(struct mosquitto *mosq, struct config *cfg);
#endif


