#include "argp_handler.h"

extern struct topic *topic_list;

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
        struct config *cfg = state->input;
        switch (key) {
                case 'h':
                        cfg->mqtt_host = arg;
                        break;
                case 'p':
                        cfg->mqtt_port = arg;
                        break;
                case 'c':
                        cfg->mqtt_use_tls = true;
                        cfg->mqtt_cert = arg;
                        break;
                case 't':

                        add_topic_to_topic_list(&topic_list, arg);
                        break;
                case 'u':
                        cfg->mqtt_use_username = true;
                        cfg->mqtt_username = arg;
                        break;
                case 'P':
                        cfg->mqtt_use_pass = true;
                        cfg->mqtt_password = arg;
                        break;
                case 'k':
                        cfg->mqtt_keepalive = arg;
                        break;
                case 's':
                        cfg->save_messages = true;
                        break;
                default:
                        return ARGP_ERR_UNKNOWN;
        }

        return 0;
}

static struct argp_option options[] = {
    {"host", 'h', "host", 0, "Host IP"},
    {"port", 'p', "port", 0, "Host port"},
    {"cafile", 'c', "cafile", 0, "Location of CA file"},
    {"topic", 't', "topic", 0, "Topic to listen to. May be repeated"},
    {"user", 'u', "user", 0, "Provide a username"},
    {"password", 'P', "password", 0, "Provide a password"},
    {"keepalive", 'k', "keepalive", 0,
     "Keep alive in seconds for this client. Defaults to 60."},
    {"save", 's', 0, 0, "Save all received messages to /var/log/mqttsub.db"},
    {0}};
static struct argp argp = {options, parse_opt, "", ""};

int get_mosq_config(struct config *cfg, int argc, char argv[]) {
        argp_parse(&argp, argc, argv, 0, 0, cfg);
        int rc = argp_validate(cfg);
        return rc;
}

int argp_validate(struct config *cfg) {
        if (strlen(cfg->mqtt_host) == 0) {
                fprintf(stderr, "ERROR: Host not given\n");
        }
        if (strlen(cfg->mqtt_port) != 0) {
                for (int i = 0; i < strlen(cfg->mqtt_port); i++) {
                        if (isdigit(cfg->mqtt_port[i]) == 0) {
                                fprintf(stderr, "ERROR: Port cannot contain non-digit characters\n");
                                return -1;
                        }
                }
                int port = atoi(cfg->mqtt_port);
                if (port <= 0 || port >= 65535) {
                        fprintf(stderr,
                                "ERROR: Port '%s' is not within allowed bounds (0-65535)\n",
                                cfg->mqtt_port);
                        return -1;
                }

                if (cfg->mqtt_use_tls == true) {
                        if (access(cfg->mqtt_cert, F_OK != 0)) {
                                fprintf(stderr, "ERROR: Could not access cafile\n");
                                return -1;
                        }
                }
                if ((cfg->mqtt_use_pass && !cfg->mqtt_use_username) || (!cfg->mqtt_use_pass && cfg->mqtt_use_username)) {
                        fprintf(stderr, "ERROR: Both username and password must be provided if one is\n");
                        return -1;
                }
        }

        /*Loop through topics to verify they're valid*/
        struct topic *curr = topic_list;
        while (curr != NULL) {
                if (validate_topic(curr->name) != 0) {
                        fprintf(stderr, "Incorrect topic. Does it contain '+' or '#'?\n");
                        return -1;
                }
                curr = curr->next;
        }
        return 0;
}

int validate_topic(char *topic) {
        if (topic == NULL) return -1;
        /* MQTT protocol considers '+' and '#' as wildcards */
        char *c = topic;
        for (int i = 0; i < strlen(topic); i++) {
                if (*c == '+' || *c == '#') return -1;
                c++;
        }
        return 0;
}
