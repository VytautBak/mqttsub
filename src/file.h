#include <sqlite3.h>
#include <stdio.h>

#include "text_formatter.h"
#ifndef FILE_H
#define FILE_H

#define LOG_FILE "/var/log/mqttsub.db"

int write_to_file(char *message, char *topic);

#endif