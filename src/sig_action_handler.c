#include "sig_action_handler.h"

struct mosquitto *mosq;
struct config *cfg;

/* Create sigaction handler */
void setup_sig_action(struct mosquitto *obj, struct config *obj2)
{
  struct sigaction term;
  struct sigaction reload;
  memset(&term, 0, sizeof(struct sigaction));
  memset(&reload, 0, sizeof(struct sigaction));

  term.sa_handler = term_proc;
  reload.sa_handler = reload_proc;
  sigaction(SIGTERM, &term, NULL);
  sigaction(SIGHUP, &reload, NULL);
  
  mosq = obj;
  cfg = obj2;
}

void term_proc(int sigterm)
{
  fprintf(stdout, "INFO: Received SIGTERM. Terminating\n");
  mosquitto_disconnect(mosq);
}

void reload_proc(int sigterm) {
  fprintf(stdout, "INFO: Received SIGHUP. Attempting to reload event list...\n");
   int rc = reload_config(cfg);
   if(rc != 0) {
     fprintf(stderr, "ERROR: Could not reload configuration. Terminating. \n");
     term_proc(SIGTERM);
   }
   if(rc == 0) {
     fprintf(stdout, "INFO: Succesfully reloaded configuration\n");
   }
}