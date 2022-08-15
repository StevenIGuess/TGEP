#include "pch.h"
#include "client.h"

namespace TGEP
{
    namespace net
    {
        template<typename T>
        client_interface<T>::client_interface() : m_Socket(m_Context)
        {

        }

        template<typename T>
        client_interface<T>::~client_interface()
        {
            Disconnect();
        }

        template<typename T>
        bool client_interface<T>::IsConnected()
        {
            if(m_Connection)
            { 
                return m_Connection->IsConnected();
            } else 
            { 
                return false; 
            }
        }

        template<typename T>
        bool client_interface<T>::Connect(const std::string &address, const uint16_t port)
        {
            try
            {
                
            }
            catch (std::exception &e)
            {
                ERROR("%s%s\n", "NETWORK_CLIENT_EXCEPTION:: ", e.what());
            }
        }

        template<typename T>
        void client_interface<T>::Disconnect()
        {
            if(IsConnected())
            {
                m_Connection->Disconnect();
            }

            m_Context.stop();
            if(m_Thread.joinable()) { m_Thread.join(); }

            m_Connection.release();
        }
    }
}