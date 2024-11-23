#include <iostream>
#include <exception>

#include <boost/asio.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include "service/impl/lua_math.h"
#include "adapters/interfaces/tcp/listener.h"

void initialize_config()
{

}

void initialize_logging()
{
    const std::string format =
        "[%TimeStamp%] [%Severity%] [%ThreadID%]: %Message%";

    boost::log::add_console_log(
        std::cout, boost::log::keywords::format = format);

    boost::log::add_file_log(
        boost::log::keywords::open_mode = std::ios::app,
        boost::log::keywords::file_name = "logs/actions_%N.log",
        boost::log::keywords::rotation_size = 5 * 1024 * 1024,
        boost::log::keywords::format = format);

    boost::log::add_common_attributes();

    // ***

    boost::log::core::get()->set_filter(
        boost::log::trivial::severity >= boost::log::trivial::trace);
}

// -----------------------------------------------------------------------

int main() /* or wrap in a class: App */ 
{
    using lez::adapters::interfaces::tcp::Listener;
    using lez::service::impl::Lua_math;

	try {
        /* config */

        /* logger */

        // initialize_logging();

        // BOOST_LOG_TRIVIAL(trace)   << "trace";
        // BOOST_LOG_TRIVIAL(debug)   << "debug";
        // BOOST_LOG_TRIVIAL(info)    << "info";
        // BOOST_LOG_TRIVIAL(warning) << "warning";
        // BOOST_LOG_TRIVIAL(error)   << "error";
        // BOOST_LOG_TRIVIAL(fatal)   << "fatal";

        /* deps */
        Lua_math math_service;

		// ***

		boost::asio::io_context ioc;
        Listener listener(ioc, math_service, 24444);
		ioc.run();
	}
    catch (const std::exception& ex) {
		std::cerr << "err: " << ex.what() << std::endl;
	}
}
