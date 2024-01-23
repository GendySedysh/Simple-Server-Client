#include "Client.h"

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cout << "Usage: ./server <name> <port> <time>" << std::endl;
		exit(0);
	}

    std::string name(argv[1]);
	int port = atoi(argv[2]);

    if (port < 1024 || port > 49151)
	{
		std::cout << "Wrong port!" << std::endl;
		exit(0);
	}

    int timeout = atoi(argv[3]);

    Client client(name, port, timeout);

    while (true)
    {
        //connect
        client.CreateSocket();
        client.SetUpSocket();
        client.ConnectToServer();

        //send messege
        client.SendMessege();

        //wait timeout
        client.WaitTimeout();
        
        //disconnect
        client.DisconnectFromServer();
    }
    
}