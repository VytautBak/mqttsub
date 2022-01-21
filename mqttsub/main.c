#include "uci_handler.h"
#include "event_handler.h"


int main(int argc, char *argv[])
{
  if(argc > 2) {
    proccess_message(argv[1], argv[2]);
  }

  return 0;
}
