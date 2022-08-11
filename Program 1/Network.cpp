#include "Network.h"
#include "Output.h"

// NetworkMember
NetworkMember::NetworkMember()
{
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0); 
    if(socketDescriptor < 0)
    {
        LOG("Can't set socket")
        //Reconnect();
    }

    socketParams.sin_family = AF_INET;
    socketParams.sin_port = htons(3426);
    socketParams.sin_addr.s_addr = htonl(INADDR_ANY);
}

void NetworkMember::Reconnect()
{
    Connected = false;
    Connect();
}

void NetworkMember::SendMessagePrototype(int __socketDescriptor)
{
    if(Connected)
    {
        int Total = 0, Len = buffer.size(), BytesWereSend;

        while(Total < Len)
        {
            BytesWereSend =  send(__socketDescriptor, buffer.data() + Total, Len - Total, 0);

            if(BytesWereSend <= 0)
            {
                LOG("Out of connection")
                Reconnect();
                break;
            }

            Total += BytesWereSend;
        }
    }
    else
    {
        LOG("Out of connection")
        Reconnect();
    }
}

void NetworkMember::RecievMessagePrototype(int __socketDescriptor)
{
   if(Connected)
   {
        int MiddleBuffer;
        int BytesToReciev; 

        BytesToReciev = recv(__socketDescriptor, &MiddleBuffer, sizeof(MiddleBuffer), 0);

        if(BytesToReciev == 0)
        {
            LOG("Out of connection")
            Reconnect();
        }

        buffer.push_back(MiddleBuffer);
   }
   else
   {
        LOG("Out of connection")
        Reconnect();
   }
}


// Client
int NetworkClient::TryToConnect()
{
    CONSOLE("Trying to connect...")

    int Result = connect(socketDescriptor, (struct sockaddr*)&socketParams, sizeof(socketParams));
    
    if(Result >= 0)
    {
        CONSOLE("Connected!")
        Connected = true;
        //Notify
    }
    else
    {
        LOG("Connection is failed\nReconnecting soon...")
        Connected = false;
    }

    return Result;
}

void NetworkClient::Connect()
{
    while(TryToConnect() < 0)
    {
        sleep(10);
        Connected = false;
      //  OnConnectionChanged.Call();
    }
    
    Connected = true;
    //Notify
    //  OnConnectionChanged.Call();
        
}

void NetworkClient::SendMessage()
{
   SendMessagePrototype(socketDescriptor);
}

void NetworkClient::RecievMessage()
{
    RecievMessagePrototype(socketDescriptor);   
}


// Server
NetworkServer::NetworkServer() : NetworkMember()
{
    if(bind(socketDescriptor, (struct sockaddr*)&socketParams, sizeof(socketParams)) < 0)
    {
        LOG("Can't bind socket")
        
        CONSOLE("Waiting while OS makes socket free... ")

        while(bind(socketDescriptor, (struct sockaddr*)&socketParams, sizeof(socketParams)) < 0)
        {
            sleep(30);
        }
    }
}

void NetworkServer::Connect()
{
    TryToConnect();
}

int NetworkServer::TryToConnect()
{
    CONSOLE("Waiting for connection...")

    listen(socketDescriptor, 1);

    clientSocketDescriptor = accept(socketDescriptor, NULL, NULL);

    if(clientSocketDescriptor < 0)
    {
        LOG("Can't accept")
    }

    Connected = true;
    CONSOLE("Connected!")

    return clientSocketDescriptor;
}

void NetworkServer::SendMessage()
{
    SendMessagePrototype(clientSocketDescriptor);
    
}

void NetworkServer::RecievMessage()
{
    RecievMessagePrototype(clientSocketDescriptor);
    
}
