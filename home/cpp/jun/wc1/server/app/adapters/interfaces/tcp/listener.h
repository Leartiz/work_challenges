#pragma once

#include <string>

#include <boost/asio.hpp>
#include <boost/asio/ip/address.hpp>

#include "client_connection.h"
#include "service/services.h"

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
                public:

                    // short names!
                public:
                    using io_context = boost::asio::io_context;
                    using tcp_acceptor = boost::asio::ip::tcp::acceptor;
                    using tcp_endpoint = boost::asio::ip::tcp::endpoint;
                    using error_code = boost::system::error_code;

                public:
                    using Services = service::Services;

                public:
                    Listener(io_context&, const Services& services, const uint16_t port);
                    Listener(io_context&, const Services& services, const tcp_endpoint&);
                    Listener(io_context&, const Services& services,
                        const std::string& ip, const uint16_t port);

                private:
                    void async_accept();
                    void accept_handler(Client_connection::ptr new_connection,
                        const error_code& error);

                private:
                    io_context& m_ioc;
                    tcp_acceptor m_tcp_acceptor;

                private:
                    const Services m_services;
                };
            }
        }        
    }
}



