#pragma once

#include <memory>
#include <string>

#include <boost/asio.hpp>

#include "delivery/tcp/handler.h"

namespace lez
{
	namespace server
	{
		namespace tcp
		{
			class client_con final :
				public std::enable_shared_from_this<client_con>
			{
				using str = std::string;

				using io_context = boost::asio::io_context;
				using socket = boost::asio::ip::tcp::socket;
				using error_code = boost::system::error_code;

				using handler = delivery::tcp::handler;

			public:
				typedef std::shared_ptr<client_con> ptr;
				static ptr create(io_context&, handler&);

			public:
				socket& sock();
				void start();

			private:
				client_con(io_context&, handler&);
				void reg_read();
				void reg_writ(std::string);

			private:
				void handle_read(const error_code&, size_t);
				void handle_writ(const error_code&, size_t);

			private:
				io_context& m_ioc;
				socket m_sock;

			private:
				handler& m_hr;
				str m_rw_msg;
			};
		}
	}
}

