#pragma once

#include <memory>

#include <boost/asio.hpp>

namespace lez
{
	class client_con : 
		public std::enable_shared_from_this<client_con>
	{
	public:
		typedef std::shared_ptr<client_con> ptr;
		static ptr create(boost::asio::io_context& ioc)
		{
			return pointer(new tcp_connection(ioc));
		}


		boost::asio::ip::tcp::socket sock;
	};
}

