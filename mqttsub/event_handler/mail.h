#include <curl/curl.h>
#include <stdio.h>
#include <string.h>

#ifndef MAIL_H
#define MAIL_H


int send_email(char *message, char *recipient, char *sender, char *url);

#endif