#include "message_parser.h"
int parse_json_message(struct variable **var, char *message)
{
  cJSON *root = cJSON_Parse(message);
  if (root == NULL) return -1;

  cJSON *element;
  cJSON_ArrayForEach(element, root)
  {
    struct variable *curr;
    if((*var)->name == NULL) {
      curr = *var;
    }
    else {
      curr = malloc(sizeof(struct variable));
      curr->next = *var;
      *var = curr;
    }


    curr->name = malloc(sizeof(char) * (strlen(element->string) + 1));
    strcpy(curr->name, element->string);

    if(element->type == cJSON_String) {
      curr->value.string = malloc(sizeof(char) * (strlen(element->valuestring) + 1));
      strcpy(curr->value.string, element->valuestring);
      curr->is_num = false;
    }
    if(element->type == cJSON_Number) {
      curr->value.num = element->valuedouble;
      curr->is_num = true;
    }

  }
  cJSON_Delete(root);
  cJSON_Delete(element);
  return 0;
}

void init_variable(struct variable *var) {
  var->name = NULL;
  var->next = NULL;
}

void delete_variable(struct variable *var) {
  struct variable *tmp;
  while(var != NULL) {
    if(var->is_num == false) free(var->value.string); 
    free(var->name);
    tmp = var;
    var = var->next;
    free(tmp);
  }
}