#include <iostream>
#include <stdexcept>

#include <boost/asio.hpp>

#include "service/service.h"
#include "service/impl/math.h"

#include "adapters/interfaces/tcp/listener.h""

int main() /* or wrap in a class: App */ 
{ 
	try {
		/* deps */
		lez::service::impl::Math math_service;

		// ***

		boost::asio::io_context ioc;
		lez::adapters::interfaces::tcp::Listener listener(ioc, math_service, 24444);

		std::cout << "Listen on: " << 24444;
		ioc.run();
	}
	catch (std::exception& ex) {
		std::cerr << "err: " << ex.what() << std::endl;
	}
}