#include "text_formatter.h"

void get_formatted_details(char *details, struct event *e, char *value) {
        char time[30];
        char operator[3];
        if (from_int_to_operator(operator, e->cmp_type) == 0) {
                get_formatted_time(time);
                sprintf(details,
                        "Event id= %d was triggered\n"
                        "Details:\n"
                        "Time: %s\n"
                        "MQTT Topic: %s\n"
                        "Variable: %s\n"
                        "Variable type: %s\n"
                        "Compare type: %d\n"
                        "Expected value: %s\n"
                        "Received message: %s\n",
                        e->id, time, e->topic, e->variable_name,
                        e->var_is_num ? "num" : "str", e->cmp_type, e->exp_value, value);
        } else
                return -1;
}

void get_formatted_payload(char *payload, char *details) {
        sprintf(payload,
                "Subject: %s\r\n"
                "\r\n" /* empty line to divide headers from body, see RFC5322 */
                "%s\r\n",
                "Triggered event", details);
}

void get_formatted_time(char *string) {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        sprintf(string, "%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900,
                tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void get_formatted_email(char *formatted, char *raw) {
        sprintf(formatted, "<%s>", raw);
}

int from_int_to_operator(char *ans, int num) {
        switch (num) {
                case 0:
                        strcpy(ans, "==");
                        return 0;
                case 1:
                        strcpy(ans, "!=");
                        return 0;
                case 2:
                        strcpy(ans, ">");
                        return 0;
                case 3:
                        strcpy(ans, ">=");
                        return 0;
                case 4:
                        strcpy(ans, "<");
                        return 0;
                case 5:
                        strcpy(ans, "<=");
                        return 0;
                default:
                        return -1;
        }
}
