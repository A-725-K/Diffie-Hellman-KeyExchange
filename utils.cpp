#include "diffie_hellman.h"

void utils::failError(string msg) {
  cerr << msg << ": " << strerror(errno) << endl;
  exit(EXIT_FAILURE);
}

bool utils::sendMessage(int sock, char *msg, size_t len) {
  return send(sock, msg, len, 0) != -1;
}

string utils::recvMessage(int sock, size_t len) {
  char *s = (char*)malloc(BUF_LEN);
  string msg;
  if (recv(sock, s, len, 0) == -1)
    utils::failError("Error executing recv()");
  if (s == NULL)
    utils::failError("Received nothing");
  msg.assign(s);
  return msg;
}

long long utils::str2ll(string str) {
  size_t sz;
  return stoll(str, &sz, 0);
}

vector<string> utils::splitString(string s) {
  istringstream is(s);
  vector<string> strings((istream_iterator<string>(is)),
			 istream_iterator<string>());
  return strings;
}
