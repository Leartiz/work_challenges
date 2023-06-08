#include <iostream>
#include <stdexcept>

#include <boost/asio.hpp>

#include "service/math.h"
#include "delivery/tcp/handler.h"
#include "server/tcp/math_lsnr.h"

int main() /* or wrap in a class: App */ 
{ 
	try {
		boost::asio::io_context ioc;

		/* deps */

		lez::delivery::tcp::handler h;


		lez::server::tcp::math_lsnr tcp_mlsnr(ioc, 24444);

		std::cout << "Listen...";
		ioc.run();
	}
	catch (std::exception& ex) {
		std::cerr << "err: " << ex.what() << std::endl;
	}
}