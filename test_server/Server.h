#pragma once

#include <vector>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <fcntl.h>
#include <poll.h>
#include <fstream>

class Server
{
private:
    int listening_;
    int port_;
	sockaddr_in hint_;
	std::vector<pollfd> client_fds;
	std::ofstream log_file_;

public:
    Server(int port_to_bind);
    ~Server();

    void CreateSocket();
    void BindSocket();
	void ListenSocket();
	void GrabConnection();
	void ProcessMessages();
	void CheckClients();
};
