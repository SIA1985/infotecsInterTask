#include "Network.h"
#include "Utils.h"

NetworkMember::NetworkMember()
{
    ownSocketDescriptor = socket(AF_INET, SOCK_STREAM, 0); 
    if(ownSocketDescriptor < 0)
    {
        LOG("Can't set socket\n")
        //Reconnect();
    }

    socketParams.sin_family = AF_INET;
    socketParams.sin_port = htons(3426);
    socketParams.sin_addr.s_addr = htonl(INADDR_ANY);
}

void NetworkMember::SendMessage()
{
    //if == 0 --- connection is lost!
    send(ownSocketDescriptor, buffer.c_str(), buffer.size(), 0); //sizeof(buff)
}

void NetworkMember::RecievMessage()
{
    int BytesToRead;
    
}


Server::Server()
{
    if(bind(ownSocketDescriptor, (struct sockaddr*)&socketParams, sizeof(socketParams)) < 0)
    {
        LOG("Can't bind socket\n")
        //Reconnect();
    }
}
