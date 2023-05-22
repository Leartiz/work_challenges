#pragma once

#include <string>

#include <boost/asio.hpp>
#include <boost/asio/ip/address.hpp>


namespace lez
{
	class math_server final
	{
    public:
        math_server(boost::asio::io_context& io_context,
            const boost::asio::ip::address& addr);

    private:
        void start_accept();
        void handle_accept(tcp_connection::pointer new_connection,
            const boost::system::error_code& error);

        boost::asio::io_context& m_io_context;
        boost::asio::ip::tcp::acceptor m_acceptor;
	};
}



