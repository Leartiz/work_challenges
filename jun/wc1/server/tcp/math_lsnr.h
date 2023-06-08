#pragma once

#include <string>

#include <boost/asio.hpp>
#include <boost/asio/ip/address.hpp>

#include "client_con.h"
#include "delivery/tcp/handler.h"

namespace lez
{
    namespace server
    {
        namespace tcp
        {
            class math_lsnr final
            {
            public:
                using io_context = boost::asio::io_context;
                using acceptor = boost::asio::ip::tcp::acceptor;
                using endpoint = boost::asio::ip::tcp::endpoint;
                using error_code = boost::system::error_code;

            public:
                math_lsnr(io_context& ioc,
                    const uint16_t port);
                math_lsnr(io_context& ioc,
                    const std::string ip, const uint16_t port);
                math_lsnr(io_context& ioc,
                    const endpoint& ep);

            private:
                void reg_accept();
                void handle_accept(client_con::ptr new_connection,
                    const error_code& error);

                io_context& m_ioc;
                acceptor m_acr;
            };
        }
    }
}



