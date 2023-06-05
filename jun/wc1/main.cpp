#include <boost/asio.hpp>

#include "math_server.h"

int main() {
	boost::asio::io_context ioc;
	lez::math_server msrv(ioc, 24444);
	ioc.run();
}