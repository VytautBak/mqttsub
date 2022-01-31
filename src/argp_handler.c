#include "argp_handler.h"

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
  struct config *cfg = state->input;
  switch (key) {
    case 'h':
      cfg->mqtt_host = arg;
      break;
    case 'p':
      cfg->mqtt_port = arg;
      break;
    case 'c':
      cfg->mqtt_cert = arg;
      break;
    case 't':
      cfg->mqtt_topics[cfg->mqtt_num_of_topics] = arg;
      cfg->mqtt_num_of_topics++;
      break;
    case 'u':
      cfg->mqtt_username = arg;
      break;
    case 'P':
      cfg->mqtt_password = arg;
      break;
    case 'k':
      cfg->mqtt_keepalive = arg;
      break;
    case 's':
      cfg->save_messages = true;
      cfg->save_file = arg;
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
    {"keepalive", 'k', "keepalive", 0, "Keep alive in seconds for this client. Defaults to 60."},
    {"save", 's', "FILE", 0, "Specify file to save all received messages to"},
    {0}};
static struct argp argp = {options, parse_opt, "", ""};

int get_mosq_config(struct config *cfg, int argc, char argv[])
{
  /* Set default values for arguments */
  cfg->mqtt_cert = "";
  cfg->mqtt_host = "";
  cfg->mqtt_password = "";
  cfg->mqtt_username = "";
  cfg->mqtt_num_of_topics = 0;
  for (int i = 0; i < MAX_NUM_OF_TOPICS; i++) cfg->mqtt_topics[i] = "";

  /* Parse arguments */
  argp_parse(&argp, argc, argv, 0, 0, cfg);
  int rc = argp_validate(cfg);
  return rc;
}

int argp_validate(struct config *cfg)
{
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
  }
  if (cfg->mqtt_num_of_topics == 0) {
    fprintf(stderr, "ERROR: No topics given\n");
    return -1;
  }

  for (int i = 0; i < cfg->mqtt_num_of_topics; i++) {
    if(validate_topic(cfg->mqtt_topics[i]) == -1) {
      fprintf(stderr, "ERROR: Invalid topic name '%s'. Does it contain '+' or '#'?\n");
    }
  }

  if (strlen(cfg->mqtt_password) != 0 && strlen(cfg->mqtt_username) == 0) {
    fprintf(stdout,
            "WARN: Cannot use password while not using username. Ignoring "
            "password...\n");
  }

  return 0;
}

int validate_topic(char *topic)
{
  /* MQTT protocol considers '+' and '#' as wildcards */
  char *c = topic;
  for(int i = 0; i < strlen(topic); i++){
    if(*c == '+' || *c == '#') return -1;
    c++;
  }
  return 0;
}
