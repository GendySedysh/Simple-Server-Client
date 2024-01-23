#include "Client.h"

Client::Client(std::string name, int port, int timeout): 
    name_(name), 
    port_(port), 
    timeout_(timeout) {}

Client::~Client() {}

void Client::CreateSocket() {
    sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_ == -1)
    {
    	std::cerr << "Failed to create socket." << std::endl;
    	exit(EXIT_FAILURE);
    }
}

void Client::SetUpSocket(){
	hint_.sin_family = AF_INET;
	hint_.sin_addr.s_addr = inet_addr("127.0.0.1");
	hint_.sin_port = htons(port_);
}

void Client::ConnectToServer() {
    int connectRes = connect(sock_, (sockaddr*)&hint_, sizeof(sockaddr));
    if (connectRes == -1) {
    	std::cerr << "Failed to connect." << std::endl;
    	exit(EXIT_FAILURE);
    }
}

void Client::SendMessege() {
    std::time_t now = std::time(NULL);
    std::tm * ptm = std::localtime(&now);

    char buffer[32];
    std::strftime(buffer, 32, "[%Y.%m.%d %H:%M:%S]", ptm);

    std::string messege(buffer);
    messege += ' ' + name_ + '\n';
    std::cout << messege;
    
    send(sock_, messege.c_str(), messege.size() + 1, 0);
}

void Client::WaitTimeout() {
    using namespace std::this_thread;
    using namespace std::chrono;

    sleep_until(system_clock::now() + seconds(timeout_));
}

void Client::DisconnectFromServer() {
    close(sock_);
}