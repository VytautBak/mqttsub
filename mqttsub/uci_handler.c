#include "uci_handler.h"

int proccess_message(char *topic, char *value)
{
  printf("attempting to parse topic = %s\n", topic);
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
    struct event e;

    if (strcmp("rule", section_type) == 0) {
      uci_foreach_element(&section->options, j)
      {
        struct uci_option *option = uci_to_option(j);
        char *option_name = option->e.name;
        e.id = k;
        if (option->type == UCI_TYPE_STRING) {
          event_parse_option(&e, option_name, option->v.string);
        } else {
          fprintf(stderr, "ERROR: There is a list type in config. Ignoring.\n");
        }
      }
      if (strcmp(topic, e.topic) == 0) {
        fprintf(stdout, "INFO: Matched input with event id=%d\n", e.id);
        if (matches_event(&e, value) == 0) {
          fprintf(stdout, "INFO: Input satisfies event id=%d check\n", e.id);
          event_execute(&e, value);
        }
      }
      k++;
    }
  }
  uci_free_context(context);
}

int uci_get_config_entry(char *path, char *value)
{
  struct uci_context *c;
  struct uci_ptr ptr;

  c = uci_alloc_context();
  int rc = uci_lookup_ptr(c, &ptr, path, true);

  if (rc != UCI_OK) {
    fprintf(stderr, "Could not find entry: \"%s\"", path);
    return rc;
  }
  strcpy(value, ptr.o->v.string);
  uci_free_context(c);
  return 0;
}


