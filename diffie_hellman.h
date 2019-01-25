#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <exception>
#include <math.h>
#include <netdb.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUF_LEN 1024
#define MAX_CONN 5
#define PORT "4444"

using namespace std;

struct pth_args {
  long long *g;
  long long *p;
  long long *private_key;

  int sock;
};

namespace utils {
  void failError(string);
  bool sendMessage(int, char*, size_t);
  string recvMessage(int, size_t);
  long long str2ll(string);
  vector<string> splitString(string);
}

namespace math {
  bool isPrime(long long);
  long long generateX(long long);
  long long powModN(long long, long long, long long);
}
