#include <TGEPNetworking.h>

enum class MessageTypes
{
	ServerAccept,
	ServerDeny,
	ServerPing,
	MessageAll,
	ServerMessage
};

class TestServer : public TGEP::net::server_interface<MessageTypes>
{
public:
	TestServer() : TGEP::net::server_interface<MessageTypes>(25556)
	{

	}

	TestServer(uint16_t port) : TGEP::net::server_interface<MessageTypes>(port)
	{

	}

protected:

	virtual bool OnClientConnect(std::shared_ptr<TGEP::net::connection<MessageTypes>> client)
	{
		return true;
	}

	virtual void OnClientDisconnect(std::shared_ptr<TGEP::net::connection<MessageTypes>> client)
	{

	}

	virtual void OnMessage(std::shared_ptr<TGEP::net::connection<MessageTypes>> client, TGEP::net::message<MessageTypes>& msg)
	{
		switch (msg.header.id)
		{
		case MessageTypes::ServerPing:
		{
			LOG("[%lu]: Server ping\n", client->GetID());

			client->Send(msg);
		}
		break;
		}
	}
};

int main(int argc, char* argv[])
{
	char* p;
	int port;

	if (argc > 1)
	{
		errno = 0;
		long conv = strtol(argv[1], &p, 10);
		if (errno != 0 || *p != '\0' || conv > INT_MAX || conv < INT_MIN) {
			printf("invalid argument!");
			return -1;
		}
		else {
			port = conv;
			printf("Starting server on port %d!\n", port);
		}
	}
	else
	{
		printf("No port specified, starting server on port 2556!\n");
		port = 2556;
	}


	TestServer server(port);
	server.Start();
	while (1)
	{
		server.Update();
	}
}

