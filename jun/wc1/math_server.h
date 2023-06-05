#pragma once

#include <string>

#include <boost/asio.hpp>
#include <boost/asio/ip/address.hpp>

namespace lez
{
    class math_server final
	{
        using io_context = boost::asio::io_context;

    public:
        math_server(boost::asio::io_context& ioc,
            const uint16_t port);
        math_server(boost::asio::io_context& ioc,
            const std::string ip, const uint16_t port);
        math_server(boost::asio::io_context& ioc,
            const boost::asio::ip::tcp::endpoint& ep);

    private:
        void reg_accept();
        void handle_accept(client_con::pointer new_connection,
            const boost::system::error_code& error);

        io_context& m_ioc;
        boost::asio::ip::tcp::acceptor m_acr;
	};
}



