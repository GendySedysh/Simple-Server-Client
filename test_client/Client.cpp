#include "Client.h"

Client::Client(std::string name, int port, int timeout): 
    name_(name), 
    port_(port), 
    timeout_(timeout) {}

Client::~Client() {}

std::string Client::GetCurretnTime()
{
    using namespace std::chrono;

    system_clock::time_point now = system_clock::now();

    microseconds ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
    time_t timer = system_clock::to_time_t(now);
    std::tm bt = *std::localtime(&timer);

    std::ostringstream oss;

    oss << std::put_time(&bt, "%Y-%m-%d %H:%M:%S");
    oss << '.' << ms.count() / 1000;

    return oss.str();
}

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
    std::ostringstream oss;
    oss << "[" << GetCurretnTime() << "]" << ' ' << name_ << '\n';

    std::string messege(oss.str());
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