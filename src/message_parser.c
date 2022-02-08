#include "message_parser.h"
int parse_json_message(struct variable **var, char *message) {
        json_object *jobj = json_tokener_parse(message);
        if (jobj == NULL) return -1;

        enum json_type type;
        json_object_object_foreach(jobj, key, val) {
                struct variable *curr;
                if ((*var)->name == NULL) {
                        curr = *var;
                } else {
                        curr = malloc(sizeof(struct variable));
                        curr->next = *var;
                        *var = curr;
                }

                strcpy(curr->name, key);
                type = json_object_get_type(val);
                switch (type) {
                        case json_type_double:
                                curr->value.num = json_object_get_double(val);
                                curr->is_num = true;
                                break;
                        case json_type_int:
                                curr->value.num = json_object_get_int(val);
                                curr->is_num = true;
                                break;
                        case json_type_string:
                                strcpy(curr->value.string, json_object_get_string(val));
                                curr->is_num = false;
                                break;
                }
        }
        json_object_put(jobj);
}

void init_variable(struct variable *var) { var->next = NULL; }

void delete_variable(struct variable *var) {
        struct variable *tmp;
        while (var != NULL) {
                tmp = var;
                var = var->next;
                free(tmp);
        }
}