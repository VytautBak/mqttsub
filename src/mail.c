#include "mail.h"
#include <string.h>
#include <stdlib.h>

struct upload_status {
  size_t bytes_read;
};

char *payload_text;

static size_t payload_source(char *ptr, size_t size, size_t nmemb, void *userp)
{
  struct upload_status *upload_ctx = (struct upload_status *)userp;
  const char *data;
  size_t room = size * nmemb;

  if ((size == 0) || (nmemb == 0) || ((size * nmemb) < 1)) {
    return 0;
  }

  data = &payload_text[upload_ctx->bytes_read];

  if (data) {
    size_t len = strlen(data);
    if (room < len) len = room;
    memcpy(ptr, data, len);
    upload_ctx->bytes_read += len;

    return len;
  }

  return 0;
}

int send_email(char *message, char *recipient, char *sender, char *url)
{
  // maybe change this?
  
  payload_text = malloc(sizeof(char) * (strlen(message) + 1));
  strcpy(payload_text, message);

  CURL *curl;
  CURLcode res = CURLE_OK;
  struct curl_slist *recipients = NULL;
  struct upload_status upload_ctx = {0};

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, sender);
    recipients = curl_slist_append(recipients, recipient);
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
    curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

    /* Send the message */
    res = curl_easy_perform(curl);

    /* Check for errors */
    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* Free the list of recipients */
    curl_slist_free_all(recipients);

    curl_easy_cleanup(curl);
    free(payload_text);
    return res;
  }
  return -1;
}
