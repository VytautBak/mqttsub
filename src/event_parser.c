#include "event_parser.h"

#define RETURN_IF_SUCCESSFUL(X) \
  if (X == 0) return 0;
int event_parse_option(struct event *e, char *option, char *value)
{
  // int rc = parse_string("topic", option, value, e->topic);
  RETURN_IF_SUCCESSFUL(parse_string("topic", option, value, e->topic));
  RETURN_IF_SUCCESSFUL(parse_string("SMTP_URL", option, value, e->smtp_url));
  RETURN_IF_SUCCESSFUL(
      parse_string("sender_email", option, value, e->sender_email));

  RETURN_IF_SUCCESSFUL(
      parse_string("SMTP_username", option, value, e->smtp_username));
  RETURN_IF_SUCCESSFUL(
      parse_string("SMTP_password", option, value, e->smtp_password));

  RETURN_IF_SUCCESSFUL(
      parse_string("expected_value", option, value, e->exp_value));

  RETURN_IF_SUCCESSFUL(
      parse_string("variable", option, value, e->variable_name));

  RETURN_IF_SUCCESSFUL(parse_email(option, value, e));

  RETURN_IF_SUCCESSFUL(parse_variable_type(option, value, e));

  RETURN_IF_SUCCESSFUL(parse_cmp_type(option, value, e));

  return -1;
}

/* This function is different from parse_email as it takes a list of emails
 * (type uci_list) */
int event_parse_emails(struct event *e, struct uci_list *list, char *option)
{
  if (strcmp("receiver_email", option) != 0) return -1;
  struct uci_element *i;
  uci_foreach_element(list, i)
  {
    char *email = malloc(sizeof(char) * 100);

    strcpy(email, i->name);


    add_to_list_end(email, &(e->receiver_emails));
  }
  return 0;
}

int parse_email(char *option, char *value, struct event *e)
{
  if (strcmp("receiver_email", option) == 0) {
    char *email = malloc(sizeof(char) * 100);

    strcpy(email, value);


    add_to_list_end(email, &(e->receiver_emails));
    return 0;
  }
  return -1;
}

int parse_string(char *expected, char *given, char *value, char *place)
{
  if (strcmp(expected, given) == 0) {
    strcpy(place, value);
    return 0;
  }
  return -1;
}

int parse_variable_type(char *option, char *value, struct event *e)
{
  if (strcmp("variable_type", option) == 0) {
    if (strcmp(value, "num") == 0) {
      e->var_is_num = true;

      return 0;
    }
    if (strcmp(value, "str") == 0) {
      e->var_is_num = false;
      return 0;
    }
    fprintf(stderr,
            "ERROR: Cannot parse event id=%d variable_type. Should be 'num' or "
            "'str', is '%s'\n",
            e->id, value);
  }

  return -1;
}

int parse_cmp_type(char *option, char *value, struct event *e)
{
  char *ptr;
  if (strcmp("compare_type", option) == 0) {
    e->cmp_type = strtol(value, &ptr, 10);
    return 0;
  }
  return -1;
}