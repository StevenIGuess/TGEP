#pragma once 

#include "tsqueue.h"
#include "message.h"
#include <asio.hpp>

namespace TGEP
{
    namespace net
    {
        template<typename T>
        class connection : public std::enable_shared_from_this<connection<T>>
        {
        public:
            connection();
            virtual ~connection();

            bool ConnectToServer();
            bool Disconnect();
            bool IsConnected() const;

            bool Send(const message<T> &msg);

        protected:
            assio::ip::tcp::socket m_Socket;

            assio::io_context &m_Context; //shared between whole asio instance 

            tsqueue<message<T>> m_MessagesOut;

            tsqueue<owned_message> &m_MessagesIn;

        }

    }
}