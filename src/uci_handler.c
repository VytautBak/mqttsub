#include "uci_handler.h"

int load_events(struct topic *topic_list) {
        struct uci_context *context = uci_alloc_context();
        struct uci_package *package;
        int id = 0;
        int rc;

        if (uci_load(context, CONFIG_NAME, &package) != UCI_OK) {
                uci_perror(context, "uci_load()");
                uci_free_context(context);
                return 1;
        }

        struct uci_element *i;
        uci_foreach_element(&package->sections, i) {
                struct uci_section *section = uci_to_section(i);
                char *section_type = section->type;
                char *section_name = section->e.name;
                struct event *event = malloc(sizeof(struct event));
                event->receiver_address = NULL;

                if (event == NULL) {
                        fprintf(stderr, "ERROR: Could not allocate memory for event \n");
                        return -1;
                }

                if (strcmp("rule", section_type) == 0) {
                        event->id = id;
                        id++;
                        rc = parse_section(section, event);
                        if (rc == 0) {
                                int rc = add_to_topic_list(topic_list, event);
                                if (rc != 0) {
                                        /*If event does not belong to any topic, it is not useful and is therefore deallocated*/
                                        wipe_mail_list(event->receiver_address);
                                        free(event);
                                }
                        } else {
                                wipe_mail_list(event->receiver_address);
                                free(event);
                        }
                } else {
                        free(event);
                }
        }
        uci_free_context(context);
        return 0;
}

int parse_section(struct uci_section *section, struct event *event) {
        struct uci_element *j;
        uci_foreach_element(&section->options, j) {
                struct uci_option *option = uci_to_option(j);
                char *option_name = option->e.name;
                if (option->type == UCI_TYPE_STRING) {
                        if (event_parse_option(event, option_name, option->v.string) != 0) {
                                fprintf(stderr,
                                        "ERROR: option '%s' with value '%s' in event id=%d could "
                                        "not be parsed. Exiting.\n",
                                        option_name, option->v.string, event->id);
                                return -1;
                        }
                } else {
                        if (event_parse_emails(event, &option->v.list, option_name) != 0) {
                                fprintf(stderr, "ERROR: List element '%s' in config is not valid\n", option_name);
                                return -1;
                        }
                }
        }
        return 0;
}
