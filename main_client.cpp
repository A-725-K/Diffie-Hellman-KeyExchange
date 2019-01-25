#include "client.h"

int main(int argc, char **argv) {
  srand(time(NULL));

  Client c("127.0.0.1");
  c.startConnection();

  exit(EXIT_SUCCESS);
}
