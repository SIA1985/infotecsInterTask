#include "Network.h"
#include "Output.h"
#include "algorithm"
#include "ProgramClasses.h"

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
    OnReconnect.Call();
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
                break;
            }

            Total += BytesWereSend;
        }
    }
    else
    {
        Reconnect();
    }
}

void NetworkMember::RecievMessagePrototype(int __socketDescriptor)
{
   if(Connected)
   {
        int Total = 0, BytesWereReciev; 

        BytesWereReciev = recv(__socketDescriptor, recvBuffer + Total, 512 - Total, 0);

        if(BytesWereReciev == 0)
            {
                Reconnect();
            }

        Total += BytesWereReciev;
        
        
        for(int i = 0; i < Total; i++)
            buffer.push_back( *(recvBuffer + i) );

   }
   else
   {
        Reconnect();
   }
}


// Client
int NetworkClient::TryToConnect()
{
    CONSOLE("\nTrying to connect...")

    int Result = connect(socketDescriptor, (struct sockaddr*)&socketParams, sizeof(socketParams));

    if(Result >= 0)
    {
        CONSOLE("Connected!\n")
        Connected = true;
        //Notify
    }
    else
    {
        LOG("Connection is failed\nReconnection in 5 seconds...\n")
        Connected = false;
    }

    return Result;
}

void NetworkClient::Connect()
{
    while(TryToConnect() < 0)
    {
        sleep(5);
        Connected = false;
      //  OnConnectionChanged.Call();
    }
    
    Connected = true;
    //Notify
    //  OnConnectionChanged.Call();
        
}

void NetworkClient::Reconnect()
{
    Connected = false;
    close(socketDescriptor);
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0); 
    OnReconnect.Call();
    Connect();
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
        LOG("\nCan't bind socket")
        
        CONSOLE("Waiting while OS makes socket free...\n")

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
    CONSOLE("\nWaiting for connection...")

    listen(socketDescriptor, 1);

    clientSocketDescriptor = accept(socketDescriptor, NULL, NULL);

    if(clientSocketDescriptor < 0)
    {
        LOG("Can't accept\n")
    }

    Connected = true;
    CONSOLE("Connected!\n")

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
