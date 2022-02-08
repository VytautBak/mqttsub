#ifndef MESSAGE_PARSER_H
#define MESSAGE_PARSER_H

#include <json-c/json.h>
#include <stdbool.h>
#include <stdio.h>

union data {
        double num;
        char string[256];
};

struct variable {
        char name[256];
        union data value;

        bool is_num;
        struct variable *next;
};

int parse_json_message(struct variable **var, char *message);
void init_variable(struct variable *var);
void delete_variable(struct variable *var);

#endif