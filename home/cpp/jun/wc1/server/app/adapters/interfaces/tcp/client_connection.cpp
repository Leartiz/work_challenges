#include <sstream>

#include <boost/bind.hpp>

#include "client_connection.h"
#include "logging/logging.h"
#include "dto/request.h"

namespace lez
{
	namespace adapters
	{
		namespace interfaces 
		{
			namespace tcp
			{
				Client_connection::Client_connection(io_context& ioc, math_service& math_service)
					: m_ioc{ ioc }, m_tcp_socket{ ioc }
					, m_deadline_timer{ ioc }
					, m_math_service{ math_service } {};

				Client_connection::ptr
					Client_connection::create(io_context& ioc, math_service& math_service)
				{
                    return std::shared_ptr<Client_connection>(
                        new Client_connection(ioc, math_service));
				}

				Client_connection::tcp_socket&
					Client_connection::get_tcp_socket()
				{
					return m_tcp_socket;
				}

				void Client_connection::start()
				{
                    async_read_next_request();
				}

				// rw
				// -------------------------------------------------------------------

                void Client_connection::async_read_next_request()
				{
					using namespace boost::asio::placeholders;
                    m_read_message = std::string(1024+4, 0);

					m_deadline_timer.expires_from_now(boost::posix_time::seconds(3));
					m_deadline_timer.async_wait(
						boost::bind(&Client_connection::deadline_handler,
							shared_from_this(), error));

                    m_tcp_socket.async_read_some(boost::asio::buffer(m_read_message),
						boost::bind(&Client_connection::read_handler,
							shared_from_this(), error, bytes_transferred));
				}

                void Client_connection::async_read_part_request()
                {
                    // TODO: !!!
                }

				void Client_connection::async_write(std::string w_message)
				{
					using namespace boost::asio::placeholders;
                    m_write_message = w_message;
                    m_tcp_socket.async_write_some(boost::asio::buffer(m_write_message),
						boost::bind(&Client_connection::write_handler,
							shared_from_this(), error, bytes_transferred));
				}

				// handlers
				// -------------------------------------------------------------------

				void Client_connection::read_handler(const error_code& err,
					size_t bytes_transferred)
				{
					m_deadline_timer.cancel();
                    if (err) {
						m_tcp_socket.close();
						return;
					}

                    // header (TCP)

                    if (bytes_transferred == 4) {
                        if (m_read_message.size() != 4) {
                            return;
                        }

                        std::string first_four = m_read_message.substr(0, 4);
                        std::uint64_t value = std::stoull(first_four);

                        if (value < bytes_transferred - 4) {
                            return;
                        }
                    }

                    // body

                    const auto body = m_read_message.substr(4);
                    const auto j = nlohmann::json::parse(body);
                    const auto r = dto::Request::from_json(j);

                    std::ostringstream sout; sout << r->to_json().dump();
                    logging::info("read: " + sout.str());

                    async_write("ok");
				}

				void Client_connection::write_handler(const error_code& err,
					size_t bytes_transferred)
				{
                    // m_timr.cancel();
                    // if (err) {
                    // 	m_sock.close();
                    // 	return;
                    // }

                    // std::cout << "wrtd: " << m_rw_msg << std::endl;
                    // reg_read();
				}

				void Client_connection::deadline_handler(const error_code& err)
				{
                    // std::cerr << "handle_wait";
                    // if (err) {
                    // 	std::cerr << "ERR";
                    // }
                    // m_sock.close();
				}
			}
		}
	}
}
