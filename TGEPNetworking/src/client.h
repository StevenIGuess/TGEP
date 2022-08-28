#pragma once
#include "NetCore.h"
#include "message.h"
#include "tsqueue.h"
#include "connection.h"

namespace TGEP
{
    namespace net
    {
        template <typename T>
        class client_interface
        {
        public:

            client_interface() : m_Socket(m_Context)
            {

            }

            virtual ~client_interface()
            {
                Disconnect();
            }

            bool Connect(const std::string& address, const uint16_t port)
            {
                try
                {
                    asio::ip::tcp::resolver resolver(m_Context);
                    asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(address, std::to_string(port));

                    m_Connection = std::make_unique<connection<T>>(
                        connection<T>::owner::client,
                        m_Context,
                        asio::ip::tcp::socket(m_Context), m_MessagesIn);

                    m_Connection->ConnectToServer(endpoints);
      

                    m_Thread = std::thread([this]() { m_Context.run(); });
                }
                catch (std::exception& e)
                {
                    ERROR("%s%s\n", "NETWORK_CLIENT_EXCEPTION:: ", e.what());
                    return false;
                }
                return true;
            }

            void Disconnect()
            {
                if (IsConnected())
                {
                    m_Connection->Disconnect();
                }

                m_Context.stop();
                if (m_Thread.joinable()) { m_Thread.join(); }

                m_Connection.release();
            }

            bool IsConnected()
            {
                if (m_Connection)
                {
                    return m_Connection->IsConnected();
                }
                else
                {
                    return false;
                }
            }
            void Send(const message<T>& msg)
            {
                if (IsConnected())
                    m_Connection->Send(msg);
            }

            tsqueue<owned_message<T>>& Incoming() { return m_MessagesIn; }

        private:
            tsqueue<owned_message<T>> m_MessagesIn;

        protected:
            asio::io_context m_Context;
            asio::ip::tcp::socket m_Socket;

            std::thread m_Thread;

            std::unique_ptr<connection<T>> m_Connection;
        };
    }
}