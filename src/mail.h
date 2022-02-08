#include <curl/curl.h>
#include <stdio.h>
#include <string.h>

#ifndef MAIL_H
#define MAIL_H

int send_email(char *message, char *sender, char *receiver, char *url, char *username, char *password);

#endif