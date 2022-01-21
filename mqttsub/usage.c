#include "usage.h"
#include <stdio.h>

void print_usage(void)
{
  int major, minor, revision;

  mosquitto_lib_version(&major, &minor, &revision);
  printf(
      "mosquitto_sub is a simple mqtt client that will subscribe to a "
      "single topic and print all messages it receives.\n");
  printf("mosquitto_sub version %s running on libmosquitto %d.%d.%d.\n\n", "0",
         major, minor, revision);
  printf(
      "Usage: mosquitto_sub [-c] [-h host] [-k keepalive] [-p port] [-q "
      "qos] [-R] -t topic ...\n");
  printf("                     [-C msg_count] [-T filter_out]\n");
#ifdef WITH_SRV
  printf("                     [-A bind_address] [-S]\n");
#else
  printf("                     [-A bind_address]\n");
#endif
  printf("                     [-i id] [-I id_prefix]\n");
  printf("                     [-d] [-N] [--quiet] [-v]\n");
  printf("                     [-u username [-P password]]\n");
  printf(
      "                     [--will-topic [--will-payload payload] "
      "[--will-qos qos] [--will-retain]]\n");
#ifdef WITH_TLS
  printf(
      "                     [{--cafile file | --capath dir} [--cert "
      "file] [--key file]\n");
  printf("                      [--ciphers ciphers] [--insecure]]\n");
#ifdef WITH_TLS_PSK
  printf(
      "                     [--psk hex-key --psk-identity identity "
      "[--ciphers ciphers]]\n");
#endif
#endif
#ifdef WITH_SOCKS
  printf("                     [--proxy socks-url]\n");
#endif
  printf("       mosquitto_sub --help\n\n");
  printf(
      " -A : bind the outgoing socket to this host/ip address. Use to "
      "control which interface\n");
  printf("      the client communicates over.\n");
  printf(
      " -c : disable 'clean session' (store subscription and pending "
      "messages when client disconnects).\n");
  printf(
      " -C : disconnect and exit after receiving the 'msg_count' "
      "messages.\n");
  printf(" -d : enable debug messages.\n");
  printf(" -h : mqtt host to connect to. Defaults to localhost.\n");
  printf(
      " -i : id to use for this client. Defaults to mosquitto_sub_ "
      "appended with the process id.\n");
  printf(
      " -I : define the client id as id_prefix appended with the process "
      "id. Useful for when the\n");
  printf("      broker is using the clientid_prefixes option.\n");
  printf(" -k : keep alive in seconds for this client. Defaults to 60.\n");
  printf(
      " -N : do not add an end of line character when printing the "
      "payload.\n");
  printf(" -p : network port to connect to. Defaults to 1883.\n");
  printf(" -P : provide a password (requires MQTT 3.1 broker)\n");
  printf(
      " -q : quality of service level to use for the subscription. "
      "Defaults to 0.\n");
  printf(" -R : do not print stale messages (those with retain set).\n");
#ifdef WITH_SRV
  printf(" -S : use SRV lookups to determine which host to connect to.\n");
#endif
  printf(
      " -t : mqtt topic to subscribe to. May be repeated multiple "
      "times.\n");
  printf(" -T : topic string to filter out of results. May be repeated.\n");
  printf(" -u : provide a username (requires MQTT 3.1 broker)\n");
  printf(" -v : print published messages verbosely.\n");
  printf(
      " -V : specify the version of the MQTT protocol to use when "
      "connecting.\n");
  printf("      Can be mqttv31 or mqttv311. Defaults to mqttv31.\n");
  printf(" --help : display this message.\n");
  printf(" --quiet : don't print error messages.\n");
  printf(
      " --will-payload : payload for the client Will, which is sent by "
      "the broker in case of\n");
  printf(
      "                  unexpected disconnection. If not given and "
      "will-topic is set, a zero\n");
  printf("                  length message will be sent.\n");
  printf(" --will-qos : QoS level for the client Will.\n");
  printf(" --will-retain : if given, make the client Will retained.\n");
  printf(" --will-topic : the topic on which to publish the client Will.\n");
#ifdef WITH_TLS
  printf(
      " --cafile : path to a file containing trusted CA certificates to "
      "enable encrypted\n");
  printf("            certificate based communication.\n");
  printf(
      " --capath : path to a directory containing trusted CA "
      "certificates to enable encrypted\n");
  printf("            communication.\n");
  printf(
      " --cert : client certificate for authentication, if required by "
      "server.\n");
  printf(
      " --key : client private key for authentication, if required by "
      "server.\n");
  printf(
      " --ciphers : openssl compatible list of TLS ciphers to "
      "support.\n");
  printf(
      " --tls-version : TLS protocol version, can be one of tlsv1.2 "
      "tlsv1.1 or tlsv1.\n");
  printf("                 Defaults to tlsv1.2 if available.\n");
  printf(
      " --insecure : do not check that the server certificate hostname "
      "matches the remote\n");
  printf(
      "              hostname. Using this option means that you cannot "
      "be sure that the\n");
  printf(
      "              remote host is the server you wish to connect to "
      "and so is insecure.\n");
  printf(
      "              Do not use this option in a production "
      "environment.\n");
#ifdef WITH_TLS_PSK
  printf(
      " --psk : pre-shared-key in hexadecimal (no leading 0x) to enable "
      "TLS-PSK mode.\n");
  printf(" --psk-identity : client identity string for TLS-PSK mode.\n");
#endif
#endif
#ifdef WITH_SOCKS
  printf(" --proxy : SOCKS5 proxy URL of the form:\n");
  printf("           socks5h://[username[:password]@]hostname[:port]\n");
  printf(
      "           Only \"none\" and \"username\" authentication is "
      "supported.\n");
#endif
  printf("\nSee http://mosquitto.org/ for more information.\n\n");
}