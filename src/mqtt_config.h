
#include <stdbool.h>
#include <stdint.h>

#include "mosquitto.h"
#include "topic_list.h"
#ifndef CONFIG_H
#define CONFIG_H

#define MAX_TOPIC_LENGTH 100
#define MAX_NUM_OF_TOPICS 10

struct config {
        char *mqtt_host;
        char *mqtt_port;
        bool mqtt_use_tls;
        char *mqtt_cert;

        bool mqtt_use_pass;
        bool mqtt_use_username;

        char *mqtt_username;
        char *mqtt_password;
        char *mqtt_keepalive;
        int mqtt_max_inflight;
        int mqtt_protocol_version;

        bool save_messages;
};
#endif