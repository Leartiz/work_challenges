#pragma once

#include <memory>
#include <string>

#include <boost/asio.hpp>
#include <boost/asio/deadline_timer.hpp>

#include "service/math_service.h"

namespace lez
{
	namespace adapters
	{
		namespace interfaces
		{
			namespace tcp
			{
				class Client_connection final :
					public std::enable_shared_from_this<Client_connection>
				{
					// short names!
				public:
					using io_context = boost::asio::io_context;
					using tcp_socket = boost::asio::ip::tcp::socket;
					using deadline_timer = boost::asio::deadline_timer;
					using error_code = boost::system::error_code;

                    using math_service = service::contract::Math_service;

				public:
					using ptr = std::shared_ptr<Client_connection>;
					static ptr create(io_context&, math_service&);

				public:
					tcp_socket& get_tcp_socket();
					void start();

				private:
					Client_connection(io_context&, math_service&);
					void async_write(std::string);

                    void async_read_next_request();
                    void async_read_part_request();

				private:
					void read_handler(const error_code&, size_t);
					void write_handler(const error_code&, size_t);
					void deadline_handler(const error_code&);

				private:
					io_context& m_ioc;
					tcp_socket m_tcp_socket;
					deadline_timer m_deadline_timer;

				private:
                    std::string m_read_message;
                    std::string m_write_message;

					// services!
				private:
                    service::contract::Math_service& m_math_service;
					//...
				};
			}
		}
	}
}

