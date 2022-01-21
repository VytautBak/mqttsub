#include "event_handler.h"

int matches_event(struct event *e, char *value)
{
  int rc = validate_types(e, value);
  if (rc != 0) return rc;
  switch (e->cmp_type) {
    case EQUAL:
      if((strcmp(e->exp_value, value) == 0)) return 0;
      return -1;
    case MORE:
      if(atoi(e->exp_value) > atoi(value)) return 0;
      return -1;
    case LESS:
      if(atoi(e->exp_value) < atoi(value)) return 0;
      return -1;
    case MORE_OR_EQUAL:
      if(atoi(e->exp_value) >= atoi(value)) return 0;
      return -1;
    case LESS_OR_EQUAL:
      if(atoi(e->exp_value) <= atoi(value)) return 0;
      return -1;
    case NOT_EQUAL:
      if(strcmp(e->exp_value, value) != 0) return 0;
      return -1;
    default:
      return -1;
  }
}

int validate_types(struct event *e, char *value)
{
  char *tmp;
  int num;
  if (e->var_is_num == true) {
    num = strtol(value, &tmp, 10);
    if (tmp == value) {
      fprintf(stderr,
              "ERROR: Input string '%s' is not a number, while rule id=%d "
              "specifies variable_type of 'num'\n",
              value, e->id);
      return -1;
    }
  }
  return 0;
}

int event_execute(struct event *e, char *value)
{
  char details[500];
  char payload[1000];
  char formatted_sender[EVENT_MAX_EMAIL_LEN];
  char formatted_receiver[EVENT_MAX_EMAIL_LEN];

  get_formatted_email(formatted_receiver, e->email);
  get_formatted_email(formatted_sender, "sender@freesmtpservers.com");
  get_formatted_details(details, e, value);
  get_formatted_payload(payload, details);

  fprintf(stdout, "INFO: Executing event id=%d.....\n", e->id);
  int rc = send_email(payload, "<receiver@freesmtpservers.com>",
             "<sender@freesmtpservers.com>", "smtp.freesmtpservers.com");
  if(rc == 0) fprintf(stdout, "INFO: Sent email succesfully!\n");
  else fprintf(stderr, "ERROR: Failed to send email. rc=%d\n",rc);
            
}

