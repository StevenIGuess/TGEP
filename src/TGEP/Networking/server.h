#pragma once 

#include "tsqueue.h"
#include "message.h"
#include "connection.h"

namespace TGEP
{
    namespace net
    {
        template<typename T>
        class server_interface
        {
        public:
            //@TODO :: add number of max connections
            server_interface(uint16_t port);
            virtual ~server_interface();

            bool Start();
            bool Stop();
            
            //ASYNC
            void WaitForClientConnection();

            //Send message to client
            void MessageClient(std::shared_ptr<connection<T>> client, const message<T> &msg);

            //Send message to all clients
            void MessageAllClients(const message<T> &msg, std::shared_ptr<connection<T>> IgnoreClient = nullptr);

            void Update(size_t MaxMessage = -1);

        protected:
            //called when client connects
            virtual bool OnClientConnect(std::shared_ptr<connection<T>> client) = 0;

            //called when client disconnect
            virtual bool OnClientDisconnect(std::shared_ptr<connection<T>> client) = 0;

            //called when server received message
            virtual void OnMessage(std::shared_ptr<connection<T>> client, message<T> &msg);

            
            //tsqueue for incoming messages
            tsqueue<owned_message<T>> m_MessagesIn;

            //active valid connections
            std::deque<std::shared_ptr<connection<T>>> m_Connections;

            asio::io_context m_AsioContext;
            std::thread m_ThreadContext;
            asio::ip::tcp::acceptor m_AsioAcceptor;

            //@TODO :: set this to number of max connections
            uint32_t nIDCounter = 10000;


        }
    }
}