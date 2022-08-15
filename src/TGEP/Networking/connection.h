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
            enum class owner
            {
                server,
                client
            };

            connection(owner parent, asio::io_context &asioContext, asio::ip::tcp::socket socket, tsqueue<owned_message<T>> &In);
            virtual ~connection();

            inline uint32_t GetID() const { return id; }

            void ConnectToClient(uint32_t uid = 0);
            bool ConnectToServer();
            bool Disconnect();
            
            bool IsConnected() const;

            bool Send(const message<T> &msg);

        protected:
            asio::ip::tcp::socket m_Socket;

            asio::io_context &m_AsioContext; //shared between whole asio instance 

            tsqueue<message<T>> m_MessagesOut;

            tsqueue<owned_message<T>> &m_MessagesIn;

            owner m_OwnerType = owner::server;
            uint32_t id = 0;

        };

    }
}