#include "pch.h"
#include "connection.h"

namespace TGEP
{
    namespace net
    {
        connection::connection(owner parent, asio::io_context &asioContext, asio::ip::tcp::socket socket, tsqueue<owned_message<T>> &In)
            : m_AsioContext(asioContext), m_Socket(socket), m_MessagesIn(In);
        {
            m_OwnerType = parent;
        }

        void connection::ConnectToClient(uint32_t uid = 0)
        {
            if( m_OwnerType == owner::server )
            {
                if(m_Socket.is_open() )
                {
                    id = uid;
                }
            }
        }

        bool connection::IsConnected() const
        {
            return m_Socket.is_open();
        }
    }
}