#include <sstream>
#include <algorithm>

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

                // -----------------------------------------------------------------

                const std::string Client_connection::get_local_addr() const
                {
                    return m_tcp_socket.local_endpoint()
                            .address().to_string();
                }

                const std::string Client_connection::get_remote_addr() const
                {
                    return m_tcp_socket.remote_endpoint()
                            .address().to_string();
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

                // read/write
                // -----------------------------------------------------------------

                void Client_connection::async_read_next_request()
				{
                    using namespace boost::posix_time;
					using namespace boost::asio::placeholders;

                    m_full_message.clear(); // to empty!
                    m_read_message = std::string(m_max_read_msg_size, 0);

                    m_deadline_timer.expires_from_now(seconds(30000));
					m_deadline_timer.async_wait(
						boost::bind(&Client_connection::deadline_handler,
							shared_from_this(), error));

                    m_tcp_socket.async_read_some(boost::asio::buffer(m_read_message),
						boost::bind(&Client_connection::read_handler,
							shared_from_this(), error, bytes_transferred));
				}

                void Client_connection::async_read_part_request()
                {
                    using namespace boost::asio::placeholders;

                    m_read_message = std::string(m_max_read_msg_size, 0);
                    m_tcp_socket.async_read_some(boost::asio::buffer(m_read_message),
                        boost::bind(&Client_connection::read_handler,
                            shared_from_this(), error, bytes_transferred));
                }

                // -----------------------------------------------------------------

				void Client_connection::async_write(std::string w_message)
				{
					using namespace boost::asio::placeholders;
                    m_write_message = w_message;
                    m_tcp_socket.async_write_some(boost::asio::buffer(m_write_message),
						boost::bind(&Client_connection::write_handler,
							shared_from_this(), error, bytes_transferred));
				}

				// handlers
                // -----------------------------------------------------------------

				void Client_connection::read_handler(const error_code& err,
					size_t bytes_transferred)
				{                    
                    if (err) {
                        logging::warning_f("client `{}` disconnected. With err: {}",
                                           get_remote_addr(), err.to_string());
						m_tcp_socket.close();
						return;
					}

                    logging::trace_f("client `{}` read byte count {}",
                                     get_remote_addr(), bytes_transferred);

                    m_full_message += std::move(
                        m_read_message.substr(0, bytes_transferred));

                    logging::trace_f("client `{}` full message size {}",
                                     get_remote_addr(), m_full_message.size());

                    // ***

                    if (m_full_message.size() > 4) {

                        auto first_four = m_full_message.substr(0, 4);
                        std::reverse(first_four.begin(), first_four.end());

                        std::uint32_t value = 0;
                        std::memcpy(&value, first_four.data(), sizeof(value));

                        if (value < m_full_message.size() - 4) {
                            async_read_part_request();
                            return;
                        }

                        if (value > m_max_full_msg_size) {
                            logging::warning_f("client `{}` disconnected. With err: {}",
                                               get_remote_addr(), "full message is too long");
                            m_tcp_socket.close();
                            return;
                        }
                    }
                    else {
                        async_read_part_request();
                        return;
                    }

                    // ***

                    try {
                        const auto body = m_full_message.substr(4); // to end!
                        const auto j_body = nlohmann::json::parse(body);
                        const auto request = dto::Request::from_json(j_body);

                        std::ostringstream sout; sout << request->to_json().dump();
                        logging::info("read: " + sout.str());
                    }
                    catch (const std::exception& e) {

                        m_tcp_socket.close();
                        return;
                    }



                    m_deadline_timer.cancel(); // !!!

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
