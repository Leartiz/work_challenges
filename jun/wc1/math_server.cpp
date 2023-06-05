#include "math_server.h"
#include "tcp_connection.h"

namespace lez
{
    using namespace std;

    using namespace boost::asio;
    using namespace boost::asio::ip;

    namespace
    {
        tcp::endpoint make_ep(const uint16_t port)
        {
            return tcp::endpoint(tcp::v4(), port);
        }

        tcp::endpoint make_ep(const std::string ipStr, const uint16_t port)
        {
            const auto ip = ip::address::from_string(ipStr);
            return tcp::endpoint(ip, port);
        }
    } // impl

    // -------------------------------------------------------------------

    math_server::math_server(boost::asio::io_context& ioc, const uint16_t port)
        : m_ioc{ ioc }, m_acr{ ioc, make_ep(port) } 
    { 
        reg_accept(); 
    };

    math_server::math_server(io_context& ioc, 
        const std::string ip, const uint16_t port)
        : m_ioc{ ioc }, m_acr{ ioc, make_ep(ip, port) } 
    {
        reg_accept();
    };

    math_server::math_server(io_context& ioc, const tcp::endpoint& ep)
        : m_ioc{ ioc }, m_acr{ ioc, ep } 
    { 
        reg_accept(); 
    };

    // -------------------------------------------------------------------

    void math_server::reg_accept()
    {
        client_con::pointer new_connection =
            tcp_connection::create(io_context_);

        m_acr.async_accept(new_connection->socket(),
            boost::bind(&tcp_server::handle_accept, this, new_connection,
                boost::asio::placeholders::error));
    }

    void math_server::handle_accept(client_con::pointer new_connection,
        const boost::system::error_code& error)
    {
        if (!error)
        {
            new_connection->start();
        }

        reg_accept();
    }
}