#include <iostream>

#include <boost/bind.hpp>

#include "listener.h"
#include "logging/logging.h"

namespace lez
{
    namespace adapters
    {
        namespace interfaces
        {
            namespace tcp
            {
                using namespace std;

                namespace
                {
                    Listener::tcp_endpoint make_tcp_endpoint(const uint16_t port)
                    {
                        return Listener::tcp_endpoint{ boost::asio::ip::tcp::v4(), port };
                    }

                    Listener::tcp_endpoint make_tcp_endpoint(const std::string& str_ip,
                        const uint16_t port)
                    {
                        const auto ip = boost::asio::ip::address::from_string(str_ip);
                        return Listener::tcp_endpoint{ ip, port };
                    }
                } // impl

                // -------------------------------------------------------

                Listener::Listener(io_context& ioc, math_service& math_service, const uint16_t port)
                    : m_ioc{ ioc }, m_tcp_acceptor{ ioc, make_tcp_endpoint(port) }
                    , m_math_service{ math_service }
                {
                    async_accept();
                }

                Listener::Listener(io_context& ioc, math_service& math_service,
                    const std::string& ip, const uint16_t port)
                    : m_ioc{ ioc }, m_tcp_acceptor{ ioc, make_tcp_endpoint(ip, port) }
                    , m_math_service{ math_service }
                {
                    async_accept();
                }

                Listener::Listener(io_context& ioc, math_service& math_service, const tcp_endpoint& ep)
                    : m_ioc{ ioc }, m_tcp_acceptor{ ioc, ep }
                    , m_math_service{ math_service }
                {
                    async_accept();
                }

                // -------------------------------------------------------

                void Listener::async_accept()
                {
                    auto new_client_connection = Client_connection::create(m_ioc, m_math_service);
                    m_tcp_acceptor.async_accept(new_client_connection->get_tcp_socket(),
                        boost::bind(&Listener::accept_handler, this, new_client_connection,
                            boost::asio::placeholders::error));
                }

                void Listener::accept_handler(Client_connection::ptr new_connection,
                    const boost::system::error_code& err)
                {
                    if (err) {
                        logging::error("math_server, handle_accept, err: " + err.message());
                    }

                    new_connection->start();
                    async_accept();
                }
            }
        }        
    }
}
