#include "pch.h"
#include "server.h"

namespace TGEP
{
    namespace net
    {
        template<typename T>
        server_interface<T>::server_interface(uint16_t port) : m_AsioAcceptor(m_AsioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
        {

        }

        template<typename T>
        server_interface<T>::~server_interface<T>()
        {
            Stop();
        }

        template<typename T>
        bool server_interface<T>::Start()
        {
            try
            {
                WaitForClientConnection();

                m_Thread = std::thread([this]() { m_AsioContext.run(); });
            }
            catch(std::exception  &e)
            {
                ERROR("%s%s\n","TGEP_SERVER_EXCEPTION:: ", e.what());
            }

            LOG("%s\n", "TGEP_SERVER::STARTED");
            return true;
        }

        template<typename T>
        bool server_interface<T>::Stop()
        {
            m_AsioContext.stop();

            if (m_Thread.joinable()) { m_Thread.join(); }

            LOG("%s", "TGEP_SERVER::STOPED");
        }

        //ASYNC
        template<typename T>
        void server_interface<T>::WaitForClientConnection()
        {
            m_AsioAcceptor.async_accept(
                [this](std::error_code ec, asio::ip::tcp::socket socket)
                {
                    if(!ec)
                    {
                        LOG("%s%s", "New connection request: ", socket.remote_endpoint())

                        std::shared_ptr<connection<T>> newconn = std::make_shared<connection<T>>(connection<T>::owner::server,
                                                                 m_AsioContext, std::move(socket), m_MessagesIn);

                        if(OnClientConnect(newconn))
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

        template<typename T>
        void server_interface<T>::MessageClient(std::shared_ptr<connection<T>> client, const message<T> &msg)
        {
            if(client && client->IsConnected())
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

        template<typename T>
        void server_interface<T>::MessageAllClients(const message<T> &msg, std::shared_ptr<connection<T>> IgnoreClient)
        {
            
            bool InvalidClientExists = false;

            for(auto &client : m_Connections)
            {
                if(client && client->IsConnected())
                {
                    if(client != IgnoreClient)
                        client->Send(msg);
                }
                else
                {
                    OnClientDisconnect(client);
                    client.reset();
                    InvalidClientExists = true;
                }
            }

            if(InvalidClientExists)
            {
                m_Connections.erase(std::remove(m_Connections.begin(), m_Connections.end(), nullptr), m_Connections.end());
            }
        }

        template<typename T>
        void server_interface<T>::Update(size_t MaxMessages)
        {
            size_t MessageCount = 0;
            while (MessageCount < MaxMessages && !m_MessagesIn.empty())
            {
                auto msg = m_MessagesIn.pop_front();

                OnMessage(msg.remote, msg.msg);

                MessageCount++;
            }
        }
    }
}