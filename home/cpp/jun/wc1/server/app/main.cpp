#include <memory>
#include <exception>

#include <boost/asio.hpp>

#include "config/config.h"

#include "logging/logging.h"
#include "logging/impl/boost/boost_logger.h"

#include "service/impl/lua_math.h"
#include "adapters/interfaces/tcp/listener.h"

using namespace lez;

// -----------------------------------------------------------------------

void initialize_logging()
{
    using logging::impl::Boost_logger;

    Boost_logger::Params default_params;
    auto logger =
            std::make_shared<Boost_logger>(
                default_params);

    logging::set_logger(logger);
}

// -----------------------------------------------------------------------

int main() /* or wrap in a class: App */ 
{
    using lez::adapters::interfaces::tcp::Listener;
    using lez::service::impl::Lua_math;

	try {

        /* config */

        const auto c = Config::instance();

        /* logger */

        initialize_logging();

        logging::trace("trace");
        logging::debug("debug");
        logging::info("info");
        logging::warning("warning");
        logging::error("error");
        logging::fatal("fatal");

        logging::info(c.to_string());

        /* deps */
        Lua_math math_service;

		// ***

		boost::asio::io_context ioc;
        Listener listener(ioc, math_service, 24444);

		ioc.run();
	}
    catch (const std::exception& ex) {
        std::stringstream sout; sout << "err: " << ex.what();
        logging::error(sout.str());
	}
}
