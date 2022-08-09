#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>

class NetworkMember
{
public:
    NetworkMember();

    virtual int Connect();

    virtual int Reconnect();

    virtual void SendMessage();

    virtual void RecievMessage();

    std::string& GetBuffer() { return buffer; }

protected:
    bool Conneted = false; //conditional_variable
    int ownSocketDescriptor = -1;
    struct sockaddr_in socketParams;

    std::string buffer;
};

class Client : public NetworkMember
{

};

class Server : public NetworkMember
{
public:
    Server() : NetworkMember();

private:
    int clientSocketDescriptor = -1;
};