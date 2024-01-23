#include "Server.h"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: ./server <port>" << std::endl;
		exit(0);
	}

	int port = atoi(argv[1]);

	if (port < 1024 || port > 49151)
	{
		std::cout << "Wrong port!" << std::endl;
		exit(0);
	}

	Server server(port);

    server.CreateSocket();
    server.BindSocket();
    server.ListenSocket();

    while (true)
    {
        server.GrabConnection();
        server.ProcessMessages();
		server.CheckClients();
    }
    
}