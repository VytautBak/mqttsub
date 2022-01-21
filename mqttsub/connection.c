#include "connection.h"

void my_message_callback(struct mosquitto *mosq, void *obj,
                         const struct mosquitto_message *message)
{
  struct mosq_config *cfg;
  int i;
  bool res;
  assert(obj);
  cfg = (struct mosq_config *)obj;
  
  if (message->payloadlen) {
    fprintf(stdout, "");
    fprintf(stdout, "Received message: %s", message->payload);
    message_check_for_events(message->topic, message->payload);
    // cia callas

    if (cfg->eol) {
      printf("\n");
    }
    fflush(stdout);
  }
}

void my_connect_callback(struct mosquitto *mosq, void *obj, int result)
{
  int i;
  struct mosq_config *cfg;

  // assert(obj);
  cfg = (struct mosq_config *)obj;

  if (!result) {
    for (i = 0; i < cfg->topic_count; i++) {
      mosquitto_subscribe(mosq, NULL, cfg->topics[i], cfg->qos);
    }
  } else {
    if (result && !cfg->quiet) {
      fprintf(stderr, "%s\n", mosquitto_connack_string(result));
    }
  }
}

void my_subscribe_callback(struct mosquitto *mosq, void *obj, int mid,
                           int qos_count, const int *granted_qos)
{
  int i;
  struct mosq_config *cfg;

  // assert(obj);
  cfg = (struct mosq_config *)obj;

  if (!cfg->quiet) printf("Subscribed (mid: %d): %d", mid, granted_qos[0]);
  for (i = 1; i < qos_count; i++) {
    if (!cfg->quiet) printf(", %d", granted_qos[i]);
  }
  if (!cfg->quiet) printf("\n");
}

void message_check_for_events(char *topic, char *message)
{
  printf("Parsing message: topic=%s  message=%s", topic, message);
  proccess_message(topic, message);
}
