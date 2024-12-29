#pragma once

#include <memory>
#include <string>

#include <boost/asio.hpp>
#include <boost/asio/deadline_timer.hpp>

#include "message_parser.h"

#include "client_request_handler.h"
#include "service/math_service.h"

namespace lez
{
	namespace adapters
	{
		namespace interfaces
		{
			namespace tcp
			{
                // or `session`!?

                class Client_connection final :
                    public std::enable_shared_from_this<Client_connection>
				{
					// short names!
				public:
					using io_context = boost::asio::io_context;
					using tcp_socket = boost::asio::ip::tcp::socket;
					using deadline_timer = boost::asio::deadline_timer;
					using error_code = boost::system::error_code;
                    using endpoint = boost::asio::ip::tcp::endpoint;

                    using math_service = service::contract::Math_service;

				public:
					using ptr = std::shared_ptr<Client_connection>;
                    static ptr create(io_context&, service::Services);

				public:
                    const std::string get_local_addr() const;
                    const std::string get_remote_addr() const;

					tcp_socket& get_tcp_socket();
					void start();

				private:                    
                    Client_connection(io_context&, const service::Services&);
                    void correct_close(const error_code& err = {});

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
                    std::uint64_t m_max_read_msg_size = 1024;
                    std::string m_read_message;
                    Message_parser m_message_parser;

                private:
                    std::string m_write_message;

					// services!
				private:
                    Client_request_handler m_handler;
				};
			}
		}
	}
}

