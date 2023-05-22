#include "math_server.h"
#include "tcp_connection.h"

namespace lez
{
    using namespace std;

    using namespace boost::asio;
    using namespace boost::asio::ip;

    math_server::math_server(io_context& io_context, const address& addr)
        : m_io_context{ io_context }
        , m_acceptor{ io_context }
    {
    }

    void math_server::start_accept()
    {
        tcp_connection::pointer new_connection =
            tcp_connection::create(io_context_);

        m_acceptor.async_accept(new_connection->socket(),
            boost::bind(&tcp_server::handle_accept, this, new_connection,
                boost::asio::placeholders::error));
    }

    void math_server::handle_accept(tcp_connection::pointer new_connection,
        const boost::system::error_code& error)
    {
        if (!error)
        {
            new_connection->start();
        }

        start_accept();
    }
}