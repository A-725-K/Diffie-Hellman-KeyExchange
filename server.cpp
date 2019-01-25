#include "server.h"

// task of thread
void* taskClient(void*);

void Server::startServer() {
  struct addrinfo getaddrinfo_hints, *server_addrinfo;
  int getaddrinfo_retval;

  memset(&getaddrinfo_hints, 0, sizeof(getaddrinfo_hints));
  
  getaddrinfo_hints.ai_family = PF_INET;
  getaddrinfo_hints.ai_socktype = SOCK_STREAM;
  getaddrinfo_hints.ai_flags = AI_PASSIVE;
  getaddrinfo_hints.ai_protocol = IPPROTO_TCP;

  if ((getaddrinfo_retval = getaddrinfo(NULL,
					PORT,
					&getaddrinfo_hints,
					&server_addrinfo)))
    utils::failError("Error executing getaddrinfo()");

  this -> server_socket = socket(server_addrinfo -> ai_family,
				 server_addrinfo -> ai_socktype,
				 server_addrinfo -> ai_protocol);
  if (this -> server_socket == -1)
    utils::failError("Error executing socket()");

  if (bind(this -> server_socket,
	   server_addrinfo -> ai_addr,
	   server_addrinfo -> ai_addrlen) == -1)
    utils::failError("Error executing bind()");

  if (listen(this -> server_socket, MAX_CONN) == -1)
    utils::failError("Error executing listen()");

  freeaddrinfo(server_addrinfo);
  cout << "Server listening on port " << PORT << "..." << endl;
  this -> serverLoopToAcceptConnections();
}

void Server::serverLoopToAcceptConnections() {
  int i;

  while (this -> nr_of_clients < MAX_CONN) {
    struct sockaddr_in client_addr;
    socklen_t addr_size = sizeof(client_addr);

    pthread_mutex_lock(&accept_mutex);
    int client_socket = accept(this -> server_socket,
			       (struct sockaddr*)&client_addr,
			       &addr_size);
    if (client_socket == -1) {
      if (errno == EINTR)
		continue;
      if (close(this -> server_socket))
		utils::failError("Error executing close()");
      utils::failError("Server could not accept this connection !");
    }
    this -> clients_sockets[this -> nr_of_clients] = client_socket;

    cout << "Received a client !" << endl;
    
    pthread_t client_thread;

    // args for the thread
    pth_args args;
    args.g = &(this -> g[this -> nr_of_clients]);
    args.p = &(this -> p[this -> nr_of_clients]);
    args.private_key = &(this -> private_key[this -> nr_of_clients]);
    args.sock = this -> clients_sockets[this -> nr_of_clients];
    
    if (pthread_create(&client_thread,
		       NULL,
		       taskClient,
		       &args) != 0)
		       utils::failError("Error executing pthread_create()");
    
    this -> clients_threads[this -> nr_of_clients] = client_thread;
    pthread_mutex_unlock(&accept_mutex);
    this -> nr_of_clients++;
  }

  for (i = 0; i < MAX_CONN; i++)
    if (pthread_join(clients_threads[i], NULL) != 0)
      utils::failError("Error executing join()");
  
  if (close(this -> server_socket))
    utils::failError("Error executing close()");
}

void* taskClient(void* vp) {
  pth_args args = *((pth_args*)vp);
  vector<string> nums;

  //for key exchange
  string msg_from;
  char * msg_to = (char*)malloc(BUF_LEN);
  long long x_b, y_a, y_b;
  
  cout << "I'm serving client " << args.sock << "..." << endl;

  msg_from = utils::recvMessage(args.sock, BUF_LEN);
  nums = utils::splitString(msg_from);
  *args.p = utils::str2ll(nums[0]);
  *args.g = utils::str2ll(nums[1]);
  y_a = utils::str2ll(nums[2]);
  x_b = math::generateX(*args.p);
  y_b = math::powModN(*args.g, x_b, *args.p);

  sprintf(msg_to, "%lld", y_b);
  utils::sendMessage(args.sock, msg_to, strlen(msg_to));

  *args.private_key = math::powModN(y_a, x_b, *args.p);
  cout << "Private key -> " << *args.private_key << endl;

  free(msg_to);
  close(args.sock);
  return NULL;
}
