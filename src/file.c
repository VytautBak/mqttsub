#include "file.h"

int write_to_file(char *filename, char *message, char *topic) {
  char time[100];
  get_formatted_time(time);
  FILE *fp;
  fp = fopen(filename, "a");
  fprintf(fp, "[%s] Received message '%s' in topic '%s'\n", time, message, topic);
  fclose(fp);
}