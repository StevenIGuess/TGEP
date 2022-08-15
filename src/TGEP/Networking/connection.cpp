#include "pch.h"
#include "connection.h"

namespace TGEP
{
    namespace net
    {
        template<typename T>
        connection<T>::connection(owner parent, asio::io_context &asioContext, asio::ip::tcp::socket socket, tsqueue<owned_message<T>> &In)
            : m_AsioContext(asioContext), m_Socket(socket), m_MessagesIn(In)
        {
            m_OwnerType = parent;
        }

        template<typename T>
        void connection<T>::ConnectToClient(uint32_t uid)
        {
            if( m_OwnerType == owner::server )
            {
                if(m_Socket.is_open() )
                {
                    id = uid;
                }
            }
        }

        template<typename T>
        bool connection<T>::IsConnected() const
        {
            return m_Socket.is_open();
        }
    }
}