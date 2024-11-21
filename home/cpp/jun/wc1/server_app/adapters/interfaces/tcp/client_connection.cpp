#include <utility>
#include <iostream>

#include <boost/bind.hpp>

#include "client_connection.h"

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
					return std::make_shared<Client_connection>(
						ioc, math_service);
				}

				Client_connection::tcp_socket&
					Client_connection::get_tcp_socket()
				{
					return m_tcp_socket;
				}

				void Client_connection::start()
				{
					async_read();
				}

				// rw
				// -------------------------------------------------------------------

				void Client_connection::async_read()
				{
					using namespace boost::asio::placeholders;
					m_rw_message = std::string(1024, 0);

					m_deadline_timer.expires_from_now(boost::posix_time::seconds(3));
					m_deadline_timer.async_wait(
						boost::bind(&Client_connection::deadline_handler,
							shared_from_this(), error));

					m_tcp_socket.async_read_some(boost::asio::buffer(m_rw_message),
						boost::bind(&Client_connection::read_handler,
							shared_from_this(), error, bytes_transferred));
				}

				void Client_connection::async_write(std::string w_message)
				{
					using namespace boost::asio::placeholders;

					m_rw_message = std::move(w_message);
					m_tcp_socket.async_write_some(boost::asio::buffer(m_rw_message),
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
						// TODO: добавить запись в лог-файл
						m_tcp_socket.close();
						return;
					}



					std::cout << "redd: " << m_rw_message << std::endl;

					// router


					async_write("ok");
				}

				void Client_connection::write_handler(const error_code& err,
					size_t bytes_transferred)
				{
					m_timr.cancel();
					if (err) {
						m_sock.close();
						return;
					}

					std::cout << "wrtd: " << m_rw_msg << std::endl;
					reg_read();
				}

				void Client_connection::deadline_handler(const error_code& err)
				{
					std::cerr << "handle_wait";
					if (err) {
						std::cerr << "ERR";
					}
					m_sock.close();
				}
			}
		}
	}
}