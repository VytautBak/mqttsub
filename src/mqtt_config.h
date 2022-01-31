
#include <stdint.h>
#include <stdbool.h>
#include "mosquitto.h"
#ifndef CONFIG_H
#define CONFIG_H

#define MAX_TOPIC_LENGTH 100
#define MAX_NUM_OF_TOPICS 10


struct config {
  char *mqtt_host;
  char *mqtt_port;
  bool mqtt_use_tls;
  char *mqtt_cert;
  char *mqtt_topics[MAX_NUM_OF_TOPICS];
  bool mqtt_use_auth;
  char *mqtt_username;
  char *mqtt_password;
  char *mqtt_keepalive;
  int mqtt_max_inflight;
  int mqtt_protocol_version;

  __uint16_t mqtt_num_of_topics;
  struct linked_list *event_list;

  char *email_url;
  char *email_sender;
  char *email_username;
  char *email_password;

  bool save_messages;
  char *save_file;
};
//char *message, char *sender, char *receiver, char *url, char *username, char *password
#endif