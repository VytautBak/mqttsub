
#include <stdint.h>


#ifndef CONFIG_H
#define CONFIG_H

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
  struct linked_list *event_list;
};

#endif