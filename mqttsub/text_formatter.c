#include "text_formatter.h"

void get_formatted_details(char *details, struct event *e, char *value)
{
  char time[30];
  get_formatted_time(time);
  sprintf(details,
          "Event id= %d was triggered\n"
          "Details:\n"
          "Time: %s\n"
          "MQTT Topic: %s\n"
          "Variable: %s\n"
          "Variable type: %s\n"
          "Compare type: %s\n"
          "Expected value: %s\n"
          "Received value: %s\n"
          "Email:%s\n",
          e->id, time, e->topic, e->variable_name,
          e->var_is_num ? "num" : "str", "cmp_type", e->exp_value, value,
          e->email);
}

void get_formatted_payload(char *payload, char *details)
{
  sprintf(payload,
          "Subject: %s\r\n"
          "\r\n" /* empty line to divide headers from body, see RFC5322 */
          "%s\r\n",
          "Triggered event", details);
}

void get_formatted_time(char *string)
{
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(string, "%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900,
          tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void get_formatted_email(char *formatted, char *raw) {
  fprintf("<%s>", raw);
}