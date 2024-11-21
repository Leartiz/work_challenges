#pragma once

#include <string>

#include <boost/asio.hpp>
#include <boost/asio/ip/address.hpp>

#include "client_connection.h"
#include "service/service.h"

namespace lez
{
    namespace adapters
    {
        namespace interfaces
        {
            namespace tcp
            {
                class Listener final
                {
                    // short names!
                public:
                    using io_context = boost::asio::io_context;
                    using tcp_acceptor = boost::asio::ip::tcp::acceptor;
                    using tcp_endpoint = boost::asio::ip::tcp::endpoint;
                    using error_code = boost::system::error_code;

                    using math_service = service::contract::Math;

                public:
                    Listener(io_context&, math_service&, const uint16_t port);
                    Listener(io_context&, math_service&, const tcp_endpoint&);
                    Listener(io_context&, math_service&, 
                        const std::string& ip, const uint16_t port);

                private:
                    void async_accept();
                    void accept_handler(Client_connection::ptr new_connection,
                        const error_code& error);

                private:
                    io_context& m_ioc;
                    tcp_acceptor m_tcp_acceptor;

                private:
                    service::contract::Math& m_math_service;
                };
            }
        }        
    }
}



