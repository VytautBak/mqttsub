#include "event_handler.h"

extern struct topic *topic_list;

int matches_event(struct event *e, struct variable *var) {
        if (e->var_is_num != var->is_num) return -1;
        if (strcmp(e->variable_name, var->name) != 0) return -1;

        char *ptr;
        double num;
        if (e->var_is_num) {
                num = strtod(e->exp_value, &ptr);
        }
        switch (e->cmp_type) {
                case EQUAL:
                        if (e->var_is_num) {
                                return num == var->value.num;
                        }
                        if ((strcmp(e->exp_value, var->value.string) == 0)) return 0;
                        return -1;
                case MORE:
                        if (num > var->value.num) return 0;
                        return -1;
                case LESS:
                        if (num < var->value.num) return 0;
                        return -1;
                case MORE_OR_EQUAL:
                        if (num >= var->value.num) return 0;
                        return -1;
                case LESS_OR_EQUAL:
                        if (num <= var->value.num) return 0;
                        return -1;
                case NOT_EQUAL:
                        if (e->var_is_num) {
                                return num != var->value.num;
                        }
                        if (strcmp(e->exp_value, var->value.string) != 0) return 0;
                        return -1;
                default:
                        return -1;
        }
}

int proccess_message(char *topic, char *message) {
        struct variable *variable = malloc(sizeof(struct variable));
        if (variable == NULL) {
                fprintf(stderr, "ERROR: Failed to allocate memory\n");
                return -1;
        }
        init_variable(variable);
        if (parse_json_message(&variable, message) != 0) {
                fprintf(stderr,
                        "ERROR: Could not parse message '%s'. Is it in JSON?\n", message);
                delete_variable(variable);
                return -1;
        }

        bool found = false;

        struct topic *curr_t = topic_list;
        while (curr_t != NULL) {
                if (strcmp(curr_t->name, topic) == 0) {
                        struct event *curr_e = curr_t->event_list;
                        while (curr_e != NULL) {
                                struct variable *curr_v = variable;
                                while (curr_v != NULL) {
                                        if (matches_event(curr_e, curr_v) == 0) {
                                                fprintf(
                                                    stdout,
                                                    "INFO: Message '%s' in topic '%s' has triggered event id=%d\n",
                                                    message, topic, curr_e->id);
                                                found = true;
                                                event_execute(curr_e, message);
                                        }

                                        curr_v = curr_v->next;
                                }
                                curr_e = curr_e->next;
                        }
                }

                curr_t = curr_t->next;
        }
        if (!found)
                fprintf(stdout,
                        "INFO: Message '%s' in topic '%s' did not trigger any events\n",
                        message, topic);
        delete_variable(variable);
}

int event_execute(struct event *e, char *value) {
        char details[500];
        char payload[1000];
        char formatted_sender[EVENT_MAX_EMAIL_LEN];
        char formatted_receiver[EVENT_MAX_EMAIL_LEN];

        get_formatted_email(formatted_sender, e->sender_email);
        get_formatted_details(details, e, value);
        get_formatted_payload(payload, details);

        fprintf(stdout, "INFO: Executing event id=%d.....\n", e->id);

        struct mail *curr = e->receiver_address;
        while (curr != NULL) {
                get_formatted_email(formatted_receiver, curr->address);
                int rc = send_email(payload, formatted_sender, formatted_receiver,
                                    e->smtp_url, e->smtp_username, e->smtp_password);
                if (rc == 0)
                        fprintf(stdout, "INFO: Sent email to '%s' succesfully!\n", curr->address);
                else
                        fprintf(stdout, "WARN: Failed to send email to '%s' \n", curr->address);

                curr = curr->next;
        }
}
