#include <curl/curl.h>
#include <stdio.h>
#include <string.h>

#ifndef MAIL_H
#define MAIL_H


void send_email(char *payload_text, char *recipient, char *sender, char *url);

#endif