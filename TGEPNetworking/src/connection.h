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

            connection(owner parent, asio::io_context& asioContext, asio::ip::tcp::socket socket, tsqueue<owned_message<T>>& In) : m_AsioContext(asioContext), m_Socket(std::move(socket)), m_MessagesIn(In)
            {
                m_OwnerType = parent;
            }

            virtual ~connection()
            {

            }

            inline uint32_t GetID() const { return id; }

            void ConnectToClient(uint32_t uid = 0)
            {
                if (m_OwnerType == owner::server)
                {
                    if (m_Socket.is_open())
                    {
                        id = uid;
                        ReadHeader();
                    }
                }
            }

            void ConnectToServer(asio::ip::tcp::resolver::results_type &endpoints)
            {
                if (m_OwnerType == owner::client)
                {
                    asio::async_connect(m_Socket, endpoints,
                        [this](std::error_code ec, asio::ip::tcp::endpoint endpoint)
                        {
                            if (!ec)
                            {
                                ReadHeader();
                            }
                        });
                }
            }

            void Disconnect()
            {
                if (!IsConnected())
                {
                    asio::post(m_AsioContext, [this]() { m_Socket.close(); });
                }
            }

            bool IsConnected() const
            {
                return m_Socket.is_open();
            }

            void Send(const message<T>& msg)
            {
                asio::post(m_AsioContext,
                    [this, msg]()
                    {
                        bool WritingMessage = !m_MessagesOut.empty();
                        m_MessagesOut.push_back(msg);
                        if (!WritingMessage)
                        {
                            WriteHeader();
                        }
                    });
            }
        
        private:

            
            void ReadHeader()
            {
                asio::async_read(m_Socket, asio::buffer(&m_MsgTempIn.header, sizeof(message_header<T>)),
                    [this](std::error_code ec, std::size_t length)
                    {
                        if (!ec)
                        {
                            if (m_MsgTempIn.header.size > 0)
                            {
                                m_MsgTempIn.body.resize(m_MsgTempIn.header.size);
                                ReadBody();
                            }
                            else
                            {
                                AddToIncomingMessageQueue();
                            }
                        }
                        else
                        {
                            ERROR("[%lu] Failed to read message header.", id);
                            m_Socket.close();
                        }
                    });
            }

            //@ASYNC
            void ReadBody()
            {
                asio::async_read(m_Socket, asio::buffer(m_MsgTempIn.body.data(), m_MsgTempIn.body.size()),
                    [this](std::error_code ec, std::size_t length)
                    {
                        if (!ec)
                        {
                            AddToIncomingMessageQueue();
                        }
                        else
                        {
                            ERROR("[%lu] Failed to read message body.", id);
                            m_Socket.close();
                        }

                    });
            }

            //@ASYNC
            void WriteHeader()
            {
                asio::async_write(m_Socket, asio::buffer(&m_MessagesOut.front().header, sizeof(message_header<T>)),
                    [this](std::error_code ec, std::size_t length)
                    {
                        if (!ec)
                        {
                            if (m_MessagesOut.front().body.size() > 0)
                            {
                                WriteBody();
                            }
                            else
                            {
                                m_MessagesOut.pop_front();

                                if (!m_MessagesOut.empty())
                                {
                                    WriteHeader();
                                }
                            }
                        }
                        else
                        {
                            ERROR("[%lu] Failed to write message header.", id);
                            m_Socket.close();
                        }
                    });
            }

            //@ASYNC
            void WriteBody()
            {
                asio::async_write(m_Socket, asio::buffer(m_MessagesOut.front().body.data(), m_MessagesOut.front().body.size()),
                    [this](std::error_code ec, std::size_t length)
                    {
                        if (!ec)
                        {
                            m_MessagesOut.pop_front();

                            if (!m_MessagesOut.empty())
                            {
                                WriteHeader();
                            }
                        }
                        else
                        {
                            ERROR("[%lu] Failed to write message body.", id);
                            m_Socket.close();
                        }

                    });
            }

            void AddToIncomingMessageQueue()
            {
                if (m_OwnerType == owner::server)
                    m_MessagesIn.push_back({ this->shared_from_this(), m_MsgTempIn });
                else
                    m_MessagesIn.push_back({ nullptr, m_MsgTempIn });

                ReadHeader();
            }

        protected:
            asio::ip::tcp::socket m_Socket;

            asio::io_context& m_AsioContext; //shared between whole asio instance 

            tsqueue<message<T>> m_MessagesOut;

            tsqueue<owned_message<T>>& m_MessagesIn;
            message<T> m_MsgTempIn;

            owner m_OwnerType = owner::server;
            uint32_t id = 0;

        };

    }
}