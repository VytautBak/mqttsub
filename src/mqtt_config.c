#include "mqtt_config.h"

void init_config(struct config *cfg) {
        /* Set the default (optional) settings */
        /* Using strings instead of ints to make input validation easier */
        cfg->mqtt_port = "1883";
        cfg->mqtt_max_inflight = 20;
        cfg->mqtt_keepalive = "60";
        cfg->mqtt_protocol_version = MQTT_PROTOCOL_V31;
        cfg->save_messages = false;
        cfg->mqtt_use_tls = false;

        cfg->mqtt_use_tls = false;
        cfg->mqtt_use_pass = false;
        cfg->mqtt_use_username = false;
        cfg->mqtt_host = "";
        cfg->mqtt_password = "";
        cfg->mqtt_username = "";
}
