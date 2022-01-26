#include "mosquitto_handler.h"

extern struct linkedlist event_list;

void mosq_connect_cb(struct mosquitto *mosq, void *obj, int result)
{
  struct config *cfg = (struct config *)obj;

  if (!result) {
    for (int i = 0; i < cfg->num_of_topics; i++) {
      mosquitto_subscribe(mosq, NULL, cfg->topics[i], 1);
    }
  } else {
    fprintf(stderr, "%s\n", mosquitto_connack_string(result));
  }
}

void mosq_message_cb(struct mosquitto *mosq, void *obj,
                     const struct mosquitto_message *message)
{
  proccess_message(message->topic, message->payload, &event_list);
}

int create_and_configure_mosq(struct mosquitto **mosq, int argc, char argv[])
{
  int rc;
  struct config *cfg = malloc(sizeof(struct config));
  if (cfg == NULL) {
    fprintf(stderr, "ERROR: Out of memory \n");
    return -1;
  }
  init_config(cfg);

  rc = get_mosq_config(cfg, argc, argv);
  if (rc != 0) return -1;

  *mosq = create_mosq(cfg);
  if (mosq == NULL) return -1;

  rc = configure_mosq(*mosq, cfg);
  if (rc != 0) return -1;

  rc = mosq_connect(*mosq, cfg);
  if (rc != 0) return -1;

  mosquitto_connect_callback_set(*mosq, mosq_connect_cb);
  mosquitto_message_callback_set(*mosq, mosq_message_cb);
  return rc;
}

struct mosquitto *create_mosq(struct config *cfg)
{
  struct mosquitto *mosq = mosquitto_new(NULL, true, cfg);
  if (!mosq) {
    switch (errno) {
      case ENOMEM:
        fprintf(stderr, "ERROR: Out of memory.\n");
        break;
      case EINVAL:
        fprintf(stderr, "ERROR: Invalid id and/or clean_session.\n");
        break;
    }
    mosquitto_lib_cleanup();
    return NULL;
  }
  return mosq;
}

void init_config(struct config *cfg)
{
  /* Set the default (optional) settings */
  /* Using strings to make input validation easier */
	cfg->port = "1883";
	cfg->max_inflight = 20;
	cfg->keepalive = "60";
	cfg->protocol_version = MQTT_PROTOCOL_V31; 
  //MQTT_PROTOCOL_V31
}

int mosq_connect(struct mosquitto *mosq, struct config *cfg)
{
  char err[1024];
  int rc = 0;

  int port = atoi(cfg->port);
  int keepalive = 60;
  rc = mosquitto_connect_bind(mosq, cfg->host, port, keepalive, NULL);
  if (rc > 0) {
    if (rc == MOSQ_ERR_ERRNO) {
      strerror_r(errno, err, 1024);
      fprintf(stderr, "ERROR: %s\n", err);
    } else {
      fprintf(stderr, "ERROR: (%s).\n", mosquitto_strerror(rc));
    }
    mosquitto_lib_cleanup();
    return rc;
  }
  return MOSQ_ERR_SUCCESS;
}

int configure_mosq(struct mosquitto *mosq, struct config *cfg)
{
  int rc;

  if (strlen(cfg->username) != 0) {
    rc = mosquitto_username_pw_set(mosq, cfg->username, cfg->password);
    if (rc != MOSQ_ERR_SUCCESS) {
      fprintf(stderr,
              "ERROR: Could not set mosquitto username and password, rc=%d",
              rc);
      // mosquitto_lib_cleanup()
      return -1;
    }
  }
  if (strlen(cfg->cert) != 0) {
    rc = mosquitto_tls_set(mosq, cfg->cert, NULL, NULL, NULL, NULL);
    if (rc != MOSQ_ERR_SUCCESS) {
      fprintf(stderr, "ERROR: Could not set CA file \n");
      // mosquitto_lib_cleanup();

      return -1;
    }
  }
  mosquitto_max_inflight_messages_set(mosq, cfg->max_inflight);

  mosquitto_opts_set(mosq, MOSQ_OPT_PROTOCOL_VERSION, &(cfg->protocol_version));
  return MOSQ_ERR_SUCCESS;
}

