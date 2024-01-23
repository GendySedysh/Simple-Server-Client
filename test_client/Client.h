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
#include <ctime>
#include <chrono>
#include <thread>

class Client
{
private:
    int sock_;
    std::string name_;
    int port_;
    int timeout_;
    sockaddr_in hint_;

public:
    Client(std::string name, int port, int timeout);
    ~Client();

    void CreateSocket();
    void SetUpSocket();
    void ConnectToServer();
    void SendMessege();
    void WaitTimeout();
    void DisconnectFromServer();
};
