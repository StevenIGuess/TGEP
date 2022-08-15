#pragma once
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

            client_interface();
            virtual ~client_interface();

            bool Connect(const std::string &address, const uint16_t port);

            void Disconnect();

            bool IsConnected();

            tsqueue<owned_message<T>> &Incoming() { return m_MessagesIn; }

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