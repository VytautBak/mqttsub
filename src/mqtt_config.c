#include "mqtt_config.h"

void init_config(struct config *cfg)
{
  /* Set the default (optional) settings */
  /* Using strings to make input validation easier */
	cfg->mqtt_port = "1883";
	cfg->mqtt_max_inflight = 20;
	cfg->mqtt_keepalive = "60";
	cfg->mqtt_protocol_version = MQTT_PROTOCOL_V31; 
  cfg->save_messages = false;
  cfg->mqtt_use_auth = false;
  cfg->mqtt_use_tls = false;
}

