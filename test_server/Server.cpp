#include "Server.h"

Server::Server(int port_to_bind): port_(port_to_bind) {
	log_file_.open("log.txt");
}

Server::~Server() {
	log_file_.close();
}

void Server::CreateSocket() {
    listening_ = socket(AF_INET, SOCK_STREAM, 0);
    if (listening_ == -1)
    {
    	std::cerr << "Failed to create socket." << std::endl;
    	exit(EXIT_FAILURE);
    }
}

void Server::BindSocket(){
	hint_.sin_family = AF_INET;
	hint_.sin_addr.s_addr = inet_addr("127.0.0.1");
	hint_.sin_port = htons(port_);
	if (bind(listening_, (sockaddr*)&hint_, sizeof(sockaddr)) < 0)
	{
		std::cout << "Failed to bind to port." << port_ << ". errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}
}

void Server::ListenSocket()
{
	if (listen(listening_, 128) < 0)
	{
		std::cerr << "Failed to listen on socket." << std::endl;
		exit(EXIT_FAILURE);
	}
	fcntl(listening_, F_SETFL, O_NONBLOCK);
}

void Server::GrabConnection()
{
	size_t addrlen = sizeof(sockaddr);
	int connection = accept(listening_, (struct sockaddr*)&hint_, (socklen_t*)&addrlen);

	if (connection >= 0)
	{
		char	host[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(hint_.sin_addr), host, INET_ADDRSTRLEN);
		struct pollfd	pfd;
		pfd.fd = connection;
		pfd.events = POLLIN;
		pfd.revents = 0;

		client_fds.push_back(pfd);
	}
}

void Server::ProcessMessages()
{
	int	pret = poll(client_fds.data(), client_fds.size(), 1);

    std::string	message;
    std::vector<std::string> message_log;
	char	buffer[1024];
	int		readed;

	if (pret != 0)
	{
		for (size_t i = 0; i < client_fds.size(); i++)
		{
			if (client_fds[i].revents & POLLIN)
			{
				readed = 0;
				memset(buffer, 0, sizeof(buffer));
				while ((readed = recv(client_fds[i].fd, buffer, 1023, 0)) > 0)
				{
					buffer[readed] = '\0';
					message += buffer;
					memset(buffer, 0, sizeof(buffer));
					if (message.find('\n') != std::string::npos)
						break;
				}
                if (message.size() > 1) {
                    message.pop_back();
                    log_file_ << message << std::endl;
                }
			}
			message.clear();
			client_fds[i].revents = 0;
		}
	}
}

void Server::CheckClients(){
	char *buf;
	size_t retval;

	for (size_t i = 0; i < client_fds.size(); i++) {
		retval = recv(client_fds[i].fd, &buf, 1, MSG_PEEK | MSG_DONTWAIT);

		if (retval == 0) {
			close(client_fds[i].fd);
            client_fds.erase(client_fds.begin() + i);
		}
		retval = 0;
	}
}