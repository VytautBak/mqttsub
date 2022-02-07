#ifndef MESSAGE_PARSER_H
#define MESSAGE_PARSER_H


#include <stdio.h>
#include <cjson/cJSON.h>
#include <stdbool.h>

union data {
  double num;
  char *string;
};

struct variable{
  char *name;
  union data value;

  bool is_num;
  struct variable *next;
};

int parse_json_message(struct variable **var, char *message);
void init_variable(struct variable *var);
void delete_variable(struct variable *var);

#endif