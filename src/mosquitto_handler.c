#include "mosquitto_handler.h"

extern struct topic *topic_list;

void mosq_connect_cb(struct mosquitto *mosq, void *obj, int result) {
        if (!result) {
                fprintf(stdout, "INFO: Succesfully connected to MQTT server\n");
                struct topic *curr = topic_list;
                while (curr != NULL) {
                        mosquitto_subscribe(mosq, NULL, curr->name, 1);
                        fprintf(stdout, "INFO: Succesfully subscribed to topic '%s'\n",
                                curr->name);
                        curr = curr->next;
                }
        } else {
                fprintf(stderr, "%s\n", mosquitto_connack_string(result));
        }
}

void mosq_message_cb(struct mosquitto *mosq, void *obj,
                     const struct mosquitto_message *message) {
        struct config *cfg = (struct config *)obj;
        proccess_message(message->topic, message->payload);
        if (cfg->save_messages == true) {
                write_to_file(message->payload, message->topic);
        }
}

int create_and_configure_mosq(struct mosquitto **mosq, struct config *cfg,
                              int argc, char argv[]) {
        mosquitto_lib_init();
        int rc;
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

struct mosquitto *create_mosq(struct config *cfg) {
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
                return NULL;
        }
        return mosq;
}

int mosq_connect(struct mosquitto *mosq, struct config *cfg) {
        char err[1024];
        int rc = 0;
        char *ptr;

        int port = strtol(cfg->mqtt_port, &ptr, 10);
        int keepalive = strtol(cfg->mqtt_keepalive, &ptr, 10);

        rc = mosquitto_connect_bind(mosq, cfg->mqtt_host, port, keepalive, NULL);
        if (rc > 0) {
                if (rc == MOSQ_ERR_ERRNO) {
                        strerror_r(errno, err, 1024);
                        fprintf(stderr, "ERROR: %s\n", err);
                } else {
                        fprintf(stderr, "ERROR: %s\n", mosquitto_strerror(rc));
                }

                return rc;
        }
        return MOSQ_ERR_SUCCESS;
}

int configure_mosq(struct mosquitto *mosq, struct config *cfg) {
        int rc;

        if (cfg->mqtt_use_pass && cfg->mqtt_use_username) {
                rc =
                    mosquitto_username_pw_set(mosq, cfg->mqtt_username, cfg->mqtt_password);
                if (rc != MOSQ_ERR_SUCCESS) {
                        fprintf(stderr,
                                "ERROR: Could not set mosquitto username and password, rc=%d",
                                rc);
                        return -1;
                }
        }
        if (cfg->mqtt_use_tls) {
                rc = mosquitto_tls_set(mosq, cfg->mqtt_cert, NULL, NULL, NULL, NULL);
                if (rc != MOSQ_ERR_SUCCESS) {
                        fprintf(stderr, "ERROR: Could not set CA file \n");
                        return -1;
                }
        }
        mosquitto_max_inflight_messages_set(mosq, cfg->mqtt_max_inflight);

        mosquitto_opts_set(mosq, MOSQ_OPT_PROTOCOL_VERSION,
                           &(cfg->mqtt_protocol_version));
        return MOSQ_ERR_SUCCESS;
}
