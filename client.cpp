#include "client.h"

Client::Client(string ip) {
  this -> p = math::generateX(1009); //for example
  this -> g = math::generateX(1009); //for example

  this -> ipaddr = ip;
}

Client::Client(long long p, long long g, string ip) {
  this -> p = p;
  this -> g = g;

  this -> ipaddr = ip;
}

void Client::startConnection() {
  struct addrinfo getaddrinfo_hints, *server_addrinfo;
  struct sockaddr_in* ipv4;
  char* ip_in_str;
  int getaddrinfo_retval;

  memset(&getaddrinfo_hints, 0, sizeof(getaddrinfo_hints));

  getaddrinfo_hints.ai_family = PF_INET;
  getaddrinfo_hints.ai_socktype = SOCK_STREAM;
  getaddrinfo_hints.ai_protocol = IPPROTO_TCP;

  if ((getaddrinfo_retval = getaddrinfo(ipaddr.c_str(),
					PORT,
					&getaddrinfo_hints,
					&server_addrinfo)))
    utils::failError("Error executing getaddrinfo()");

  ipv4 = (struct sockaddr_in*)server_addrinfo -> ai_addr;
  ip_in_str = (char *)this -> ipaddr.c_str();
  cout << "Client trying to connect to server "
       << this -> ipaddr
       << "("
       << inet_ntop(PF_INET, &ipv4 -> sin_addr, ip_in_str, INET_ADDRSTRLEN)
       << ") on port "
       << PORT
       << "..." << endl;

  this -> client_socket = socket(server_addrinfo -> ai_family,
				 server_addrinfo -> ai_socktype,
				 server_addrinfo -> ai_protocol);
  if (this -> client_socket == -1)
    utils::failError("Error executing socket()");
  if (connect(this -> client_socket,
	      server_addrinfo -> ai_addr,
	      server_addrinfo -> ai_addrlen) == -1)
    utils::failError("Error executing connect()");

  freeaddrinfo(server_addrinfo);

  this -> keyExchange();
  close(this -> client_socket);
}

void Client::keyExchange() {
  //for key exchange
  string msg_from;
  char* msg_to = (char*)malloc(BUF_LEN);
  long long x_a, y_a, y_b;

  x_a = math::generateX(this -> p);
  y_a = math::powModN(this -> g, x_a, this -> p);
  
  //send the chosen values
  cout << "STARTING DIFFIE-HELLMAN PROTOCOL..." << endl;  

  sprintf(msg_to, "%lld %lld %lld", this -> p, this -> g, y_a);
  utils::sendMessage(client_socket, msg_to, strlen(msg_to));
  
  msg_from = utils::recvMessage(this -> client_socket, BUF_LEN);
  y_b = utils::str2ll(msg_from);
  this -> private_key = math::powModN(y_b, x_a, this -> p);
  
  cout << "Private key -> " << this -> private_key << endl;
  free(msg_to);
}
