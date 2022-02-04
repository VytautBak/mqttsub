#include "event_handler.h"

extern struct linked_list topic_list;

int matches_event(struct event *e, char *topic, char *value)
{
  int rc = strcmp(e->topic, topic);
  if (rc != 0) return -1;

  rc = validate_types(e, value);
  if (rc != 0) return rc;
  switch (e->cmp_type) {
    case EQUAL:
      if ((strcmp(e->exp_value, value) == 0)) return 0;
      return -1;
    case MORE:
      if (atoi(e->exp_value) > atoi(value)) return 0;
      return -1;
    case LESS:
      if (atoi(e->exp_value) < atoi(value)) return 0;
      return -1;
    case MORE_OR_EQUAL:
      if (atoi(e->exp_value) >= atoi(value)) return 0;
      return -1;
    case LESS_OR_EQUAL:
      if (atoi(e->exp_value) <= atoi(value)) return 0;
      return -1;
    case NOT_EQUAL:
      if (strcmp(e->exp_value, value) != 0) return 0;
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
      /* fprintf(stderr,
               "ERROR: Input string '%s' is not a number, while rule id=%d "
               "specifies variable_type of 'num'\n",
               value, e->id);*/
      return -1;
    }
  }
  return 0;
}

int proccess_message(char *topic, char *message)
{
  bool found = false;

  struct Node *curr = topic_list.first;
  struct topic *t;
  struct event *e;
  while (curr != NULL) {
    t = curr->data;
    if (strcmp(topic, t->name) == 0) {
      struct Node *tmp = t->events.first;
      while (tmp != NULL) {
        e = tmp->data;
        if (matches_event(e, topic, message) == 0) {
          fprintf(
              stdout,
              "INFO: Message '%s' in topic '%s' has triggered event id=%d\n",
              message, topic, e->id);
          found = true;
          event_execute(e, message);
        }
        tmp = tmp->next;
      }
    }
    curr = curr->next;
  }
  if (!found)
    fprintf(stdout,
            "INFO: Message '%s' in topic '%s' did not trigger any events\n",
            message, topic);

  /*
  while (curr != ll->last) {
    if (matches_event(&(curr->data), topic, message) == 0) {
      struct event *e = curr->data;
      fprintf(stdout,
              "INFO: Message '%s' in topic '%s' has triggered event id=%d\n",
              message, topic, e->id);
      event_execute(&(curr->data), message);
      found = true;
    }

    curr = curr->next;
  }
  if (!found)
    fprintf(stdout,
            "INFO: Message '%s' in topic '%s' did not trigger any events\n",
            message, topic);*/
}

int event_execute(struct event *e, char *value)
{
  char details[500];
  char payload[1000];
  char formatted_sender[EVENT_MAX_EMAIL_LEN];
  char formatted_receiver[EVENT_MAX_EMAIL_LEN];

  get_formatted_email(formatted_sender, e->sender_email);
  get_formatted_details(details, e, value);
  get_formatted_payload(payload, details);

  fprintf(stdout, "INFO: Executing event id=%d.....\n", e->id);

  struct Node *curr = e->receiver_emails.first;
  while (curr != NULL) {
    get_formatted_email(formatted_receiver, curr->data);

    /* printf("sender:%s\nreceiver:%s\nurl:%s\nuser:%s\npassword:%s\n",
       formatted_sender, formatted_receiver, e->smtp_url, e->smtp_username,
       e->smtp_password);*/
    int rc = send_email(payload, formatted_sender, formatted_receiver,
                        e->smtp_url, e->smtp_username, e->smtp_password);
    if (rc == 0)
      fprintf(stdout, "INFO: Sent email succesfully!\n");
    else
      fprintf(stderr, "ERROR: Failed to send email. rc=%d\n", rc);
    curr = curr->next;
  }
}
