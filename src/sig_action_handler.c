#include "sig_action_handler.h"

struct mosquitto *mosq;

/* Create sigaction handler */
void setup_sig_action(struct mosquitto *obj, struct config *obj2)
{
  struct sigaction term;
  memset(&term, 0, sizeof(struct sigaction));
  term.sa_handler = term_proc;
  sigaction(SIGTERM, &term, NULL);
  mosq = obj;
}

void term_proc(int sigterm)
{
  fprintf(stdout, "INFO: Received SIGTERM. Terminating\n");
  mosquitto_disconnect(mosq);
}
