#pragma once 
#include "NetCore.h"
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
            server_interface(uint16_t port) : m_AsioAcceptor(m_AsioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
            {

            }
            virtual ~server_interface()
            {
                Stop();
            }

            bool Start()
            {
                try
                {
                    WaitForClientConnection();

                    m_Thread = std::thread([this]() { m_AsioContext.run(); });
                }
                catch (std::exception& e)
                {
                    ERROR("%s%s\n", "TGEP_SERVER_EXCEPTION:: ", e.what());
                }

                LOG("%s\n", "TGEP_SERVER::STARTED");
                return true;
            }

            void Stop()
            {
                m_AsioContext.stop();

                if (m_Thread.joinable()) { m_Thread.join(); }

                LOG("%s", "TGEP_SERVER::STOPED");

            }

            //ASYNC
            void WaitForClientConnection()
            {
                m_AsioAcceptor.async_accept(
                    [this](std::error_code ec, asio::ip::tcp::socket socket)
                    {
                        if (!ec)
                        {
                            LOG("%s%s\n", "New connection request: ", socket.remote_endpoint().address().to_string());

                            std::shared_ptr<connection<T>> newconn = std::make_shared<connection<T>>(connection<T>::owner::server, m_AsioContext, std::move(socket), m_MessagesIn);

                            if (OnClientConnect(newconn))
                            {
                                //connection accepted
                                m_Connections.push_back(std::move(newconn));

                                m_Connections.back()->ConnectToClient(nIDCounter++);

                                LOG("%s%i%s", "Connection request accepted [ID:", m_Connections.back()->GetID(), "]\n")
                            }
                            else
                            {
                                LOG("Connection Denied!\n")
                            }
                        }
                        else
                        {
                            ERROR("%s%s\n", "TGEP_SERVER_EXCEPTION:: ", ec.message());
                        }

                        WaitForClientConnection();
                    });
            }

            //Send message to client
            void MessageClient(std::shared_ptr<connection<T>> client, const message<T>& msg)
            {
                if (client && client->IsConnected())
                {
                    client->Send(msg);
                }
                else
                {
                    OnClientDisconnect(client);
                    client.reset();
                    m_Connections.erase(std::remove(m_Connections.begin(), m_Connections.end(), client), m_Connections.end());
                }
            }

            //Send message to all clients
            void MessageAllClients(const message<T>& msg, std::shared_ptr<connection<T>> IgnoreClient = nullptr)
            {

                bool InvalidClientExists = false;

                for (auto& client : m_Connections)
                {
                    if (client && client->IsConnected())
                    {
                        if (client != IgnoreClient)
                            client->Send(msg);
                    }
                    else
                    {
                        OnClientDisconnect(client);
                        client.reset();
                        InvalidClientExists = true;
                    }
                }

                if (InvalidClientExists)
                {
                    m_Connections.erase(std::remove(m_Connections.begin(), m_Connections.end(), nullptr), m_Connections.end());
                }
            }

            void Update(size_t MaxMessages = -1)
            {
                size_t MessageCount = 0;
                while (MessageCount < MaxMessages && !m_MessagesIn.empty())
                {

                    auto msg = m_MessagesIn.pop_front();

                    OnMessage(msg.remote, msg.msg);

                    MessageCount++;
                }
            }

        protected:
            //called when client connects
            virtual bool OnClientConnect(std::shared_ptr<connection<T>> client) { return false; }

            //called when client disconnect
            virtual void OnClientDisconnect(std::shared_ptr<connection<T>> client) { }

            //called when server received message
            virtual void OnMessage(std::shared_ptr<connection<T>> client, message<T>& msg) { };


            //tsqueue for incoming messages
            tsqueue<owned_message<T>> m_MessagesIn;

            //active valid connections
            std::deque<std::shared_ptr<connection<T>>> m_Connections;

            asio::io_context m_AsioContext;
            std::thread m_Thread;
            asio::ip::tcp::acceptor m_AsioAcceptor;

            //@TODO :: set this to number of max connections
            uint32_t nIDCounter = 10000;


        };
    }
}