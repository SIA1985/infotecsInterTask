#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>

#include "ProgramClasses.h"

class NetworkMember
{
public:
    Delegate OnReconnect;


    NetworkMember();

    virtual ~NetworkMember() {close(socketDescriptor); delete recvBuffer; }     


    virtual int TryToConnect(){ return 0; }

    virtual void Reconnect();

    virtual void Connect(){}

    virtual void SendMessage(){}

    virtual void RecievMessage(){}

    std::string& GetBuffer() { return buffer; }

    void ClearBuffer() { buffer.clear(); }

    bool IsConnected() { return Connected; }

protected:
    bool Connected = false; 
    int socketDescriptor = -1;
    struct sockaddr_in socketParams;

    std::string buffer;
    char* recvBuffer = new char[512];

    void SendMessagePrototype(int __socketDescriptor);

    void RecievMessagePrototype(int __socketDescriptor);
};

class NetworkClient : public NetworkMember
{
public:
    int TryToConnect() override;

    void Connect() override;

    void Reconnect() override;

    void SendMessage() override;

    void RecievMessage() override;
};

class NetworkServer : public NetworkMember
{
public:
    NetworkServer();

    int TryToConnect() override;
    
    void Connect() override;

    void SendMessage() override;

    void RecievMessage() override;

private:
    int clientSocketDescriptor = -1;
};
