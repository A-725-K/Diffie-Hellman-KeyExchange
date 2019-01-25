#include "diffie_hellman.h"

class Client {
 private:
  /* for key exchange */
  long long private_key;
  long long p;
  long long g;

  /* for connection */
  string ipaddr;
  int client_socket;

  /* functions */
  void keyExchange();

 public:
  /* constructors */
  Client(string);
  Client(long long, long long, string);

  /* functions */
  void startConnection();
};
