#include "pch.h"
#include "client.h"

namespace TGEP
{
    namespace net
    {
        client_interface::client_interface() : m_Socket(m_Context)
        {

        }

        client_interface::~client_interface()
        {
            Disconnect();
        }

        bool client_interface::IsConnected()
        {
            if(m_Connection)
            { 
                return m_connection->IsConnected();
            } else 
            { 
                return false; 
            }
        }

        bool client_interface::Connect(const std::string &address, const std::string &port)
        {
            try
            {
                m_Connection = std::make_unique<Connection<T>>(); //todo

                assio::ip::tcp::resolver resolver(m_Context);
                m_Endpoints = resolver.resolve(address, std::to_string(port));

                m_Connection->ConnectToServer(m_Endpoints);

                m_Thread = std::thread([this]() { m_Context.run(); });
            }
            catch (std::exception &e)
            {
                ERROR("%s%s\n", "NETWORK_CLIENT_EXCEPTION:: ", e.what());
            }
        }

        void client_interface::Disconnect()
        {
            if(IsConnected())
            {
                m_connection->Disconnect();
            }

            m_Context.stop();
            if(m_Thread.joinable()) { m_Thread.join(); }

            m_connection.release();
        }
    }
}