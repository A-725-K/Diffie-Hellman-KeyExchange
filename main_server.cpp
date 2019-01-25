#include "server.h"

int main(int argc, char **argv) {
  srand(time(NULL));
  
  Server s;
  s.startServer();

  exit(EXIT_SUCCESS);
}
