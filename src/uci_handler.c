#include "uci_handler.h"



/**
 * Get a string representation of a uci_list structure.
 * 
 * IMPORTANT: the returned string must be freed by the caller.
 */
char *uci_list_to_string(struct uci_list *list)
{
    size_t max_size = 100;
    size_t current_size = 1;    // This includes the null terminator
    char *result = calloc(max_size, sizeof(char));
    struct uci_element *i;

    uci_foreach_element(list, i)
    {
        // +2 for ", " after each list element
        size_t element_length = strlen(i->name) + 2;
        char name[element_length + 2];
        strcpy(name, i->name);
        printf("name = %s\n", name);
        if (current_size + element_length > max_size)
        {
            max_size = max_size * 2 + element_length;
            result = realloc(result, sizeof(char) * max_size);
        }
        printf("result = %s \n", result);
        strcat(result, strcat(name, ", "));
        current_size += element_length;
    }

    // Remove trailing ", "
    if (current_size >= 3)
        result[current_size - 3] = '\0';
    else
        result[0] = '\0';

    return result;
}



int load_events(struct linked_list *list)
{
  init_list(list);
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
    struct event event;

    if (strcmp("rule", section_type) == 0) {
      bool event_is_valid = true;
      uci_foreach_element(&section->options, j)
      {
        struct uci_option *option = uci_to_option(j);
        char *option_name = option->e.name;

        /*Set the defaults for event*/
        event.id = k;
        event.num_of_emails = 0;
        if (option->type == UCI_TYPE_STRING) {
          if (event_parse_option(&event, option_name, option->v.string) != 0) {
            event_is_valid = false;
            fprintf(stdout,
                    "WARN: option '%s' with value '%s' in event id=%d could "
                    "not be parsed. Ignoring.\n",
                    option_name, option->v.string, event.id);
          }
        } else {
          /* To parse a 'list' type (most likely email) we need to convert it to a string type first and then deallocate it*/
          event_parse_emails(&event, &option->v.list, option_name); 
        }
      }
      if (event_is_valid) add_to_list_end(event, list);
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
