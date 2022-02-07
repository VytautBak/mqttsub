#include "uci_handler.h"

int load_events(struct topic *topic_list)
{
  struct uci_context *context = uci_alloc_context();
  struct uci_package *package;

  if (uci_load(context, CONFIG_NAME, &package) != UCI_OK) {
    uci_perror(context, "uci_load()");
    uci_free_context(context);
    return 1;
  }

  struct uci_element *i, *j;  // Iteration variables
  int k = 0;
  uci_foreach_element(&package->sections, i)
  {
    struct uci_section *section = uci_to_section(i);
    char *section_type = section->type;
    char *section_name = section->e.name;
    struct event *event= malloc(sizeof(struct event));
    event->receiver_address = NULL;

    if (event == NULL) {
      fprintf(stderr, "ERROR: Could not allocate memory for event \n");
      return -1;
    }

    if (strcmp("rule", section_type) == 0) {
      bool event_is_valid = true;
      uci_foreach_element(&section->options, j)
      {
        struct uci_option *option = uci_to_option(j);
        char *option_name = option->e.name;

        /*Set the defaults for event*/
        event->id = k;

        if (option->type == UCI_TYPE_STRING) {
          if (event_parse_option(event, option_name, option->v.string) != 0) {
            event_is_valid = false;
            fprintf(stdout,
                    "WARN: option '%s' with value '%s' in event id=%d could "
                    "not be parsed. Ignoring.\n",
                    option_name, option->v.string, event->id);
          }
        } else {
          event_parse_emails(event, &option->v.list, option_name);
        }
      }
      if (event_is_valid) {
        int rc = add_to_topic_list(topic_list, event);
        if(rc != 0) {
        //wipe_list(&(event->receiver_emails), true);
        free(event);
        }
      }
      else {
       // wipe_list(&(event->receiver_emails), true);
        free(event);
      }
      k++;
    }
    else {
      free(event);
    }
  }
  uci_free_context(context);
}
