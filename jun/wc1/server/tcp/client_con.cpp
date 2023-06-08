#include <utility>
#include <iostream>

#include "client_con.h"

#include <boost/bind.hpp>

namespace lez
{
	namespace server
	{
		namespace tcp
		{
			client_con::client_con(io_context& ioc, handler& hr)
				: m_ioc{ ioc }, m_sock{ ioc }, m_hr{ hr } {};

			client_con::ptr client_con::create(io_context& ioc, handler& hr)
			{
				return ptr(new client_con(ioc, hr));
			}

			client_con::socket& client_con::sock()
			{
				return m_sock;
			}

			void client_con::start()
			{
				reg_read();
			}

			// -------------------------------------------------------------------

			void client_con::reg_read()
			{
				m_rw_msg = std::string(1024, 0);
				using namespace boost::asio::placeholders;
				m_sock.async_read_some(boost::asio::buffer(m_rw_msg),
					boost::bind(&client_con::handle_read, shared_from_this(),
						error, bytes_transferred));
			}

			void client_con::reg_writ(std::string w_msg)
			{
				m_rw_msg = std::move(w_msg);
				using namespace boost::asio::placeholders;
				m_sock.async_write_some(boost::asio::buffer(m_rw_msg),
					boost::bind(&client_con::handle_writ, shared_from_this(),
						error, bytes_transferred));
			}

			// -------------------------------------------------------------------

			void client_con::handle_read(const error_code& err,
				size_t bytes_transferred)
			{
				std::cout << "redd: " << m_rw_msg << std::endl;


				reg_writ("ok");
			}

			void client_con::handle_writ(const error_code& err,
				size_t bytes_transferred)
			{
				std::cout << "wrtd: " << m_rw_msg << std::endl;
			}
		}
	}
}