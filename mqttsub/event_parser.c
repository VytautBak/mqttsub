#include "event_parser.h"

int event_parse_option(struct event *e, char *option, char *value)
{
  if (strcmp("topic", option) == 0) {
    strcpy(e->topic, value);
    return 0;
  }
  if (strcmp("variable_type", option) == 0) {
    if (strcmp("str", value) == 0) {
      e->var_is_num = false;
      return 0;
    }
    if (strcmp("num", value) == 0) {
      e->var_is_num = true;
      return 0;
    }
    fprintf(stderr,
            "ERROR: Cannot parse event id=%d variable_type. Should be 'num' or "
            "'str', is '%s'\n",
            e->id, value);
  }
  if (strcmp("compare_type", option) == 0) {
    if (strcmp(">=", value) == 0) {
      e->cmp_type = MORE_OR_EQUAL;
      return 0;
    }
    if (strcmp("<=", value) == 0) {
      e->cmp_type = LESS_OR_EQUAL;
      return 0;
    }
    if (strcmp("==", value) == 0) {
      e->cmp_type = EQUAL;
      return 0;
    }
    if (strcmp("!=", value) == 0) {
      e->cmp_type = NOT_EQUAL;
      return 0;
    }
    if (strcmp(">", value) == 0) {
      e->cmp_type = MORE;
      return 0;
    }
    if (strcmp("<", value) == 0) {
      e->cmp_type = LESS;
      return 0;
    }
  }
  if (strcmp("expected_value", option) == 0) {
    strcpy(e->exp_value, value);
    return 0;
  }
  if (strcmp("variable", option) == 0) {
    strcpy(e->variable_name, value);
    return 0;
  }
  if (strcmp("email", option) == 0) {
    strcpy(e->email, value);
    return 0;
  }
}