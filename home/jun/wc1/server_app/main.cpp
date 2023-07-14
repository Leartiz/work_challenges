#include <iostream>
#include <stdexcept>

#include <boost/asio.hpp>

#include "service/impl/math.h"
#include "delivery/tcp/handler.h"
#include "server/tcp/math_lsnr.h"

int main() /* or wrap in a class: App */ 
{ 
	try {
		/* deps */
		lez::service::impl::math math;
		lez::delivery::tcp::handler h{ math };

		// ***

		boost::asio::io_context ioc;
		lez::server::tcp::math_lsnr tcp_mlsnr(ioc, h, 24444);

		std::cout << "Listen...";
		ioc.run();
	}
	catch (std::exception& ex) {
		std::cerr << "err: " << ex.what() << std::endl;
	}
}