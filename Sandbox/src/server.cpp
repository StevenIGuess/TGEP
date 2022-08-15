#include <Networking/server.h>
#include <Networking/message.h>
#include <Networking/connection.h>
#include <Networking/tsqueue.h>

enum class MessageType : int32_t 
{
    ServerAccept,
    ServerDeny, 
    ServerPing, 
    MessageAll, 
    ServerMessage,
};

class Server : public TGEP::net::server_interface<MessageType>
{
public:
    Server(uint16_t port) : TGEP::net::server_interface<MessageType>(port)
    {

    }
protected:

    virtual bool OnClientConnect(std::shared_ptr<TGEP::net::connection<MessageType>> client)
    {
        return true;
    }

    virtual bool OnClientDisconnect(std::shared_ptr<TGEP::net::connection<MessageType>> client)
    {
        return true;
    }

    virtual void OnMessage(std::shared_ptr<TGEP::net::connection<MessageType>> client, TGEP::net::message<MessageType> &msg)
    {

    }
};

int main()
{
    Server server(25556);
    server.Start();

    while(1)
    {
        server.Update();
    }
    return 0;
}