#include <stdio.h>
#include "text_formatter.h"
#include <sqlite3.h>
#ifndef FILE_H
#define FILE_H

#define LOG_FILE "/var/log/mqttsub.db"

int write_to_file(char *message, char *topic);




#endif