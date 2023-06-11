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
                using str = std::string;

                using io_context = boost::asio::io_context;
                using acceptor = boost::asio::ip::tcp::acceptor;
                using endpoint = boost::asio::ip::tcp::endpoint;
                using error_code = boost::system::error_code;

                using handler = delivery::tcp::handler;

            public:
                math_lsnr(io_context&, handler&, const uint16_t port);
                math_lsnr(io_context&, handler&, const str& ip, const uint16_t port);
                math_lsnr(io_context&, handler&, const endpoint&);

            private:
                void reg_accept();
                void handle_accept(client_con::ptr new_connection,
                    const error_code& error);

            private:
                io_context& m_ioc;
                acceptor m_acr;
                handler& m_hr;
            };
        }
    }
}



