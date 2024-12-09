#include <memory>
#include <string>
#include <exception>

#include <boost/asio.hpp>

#include "config/config.h"

#include "logging/logging.h"
#include "logging/impl/boost/boost_logger.h"

#include "service/impl/lua_math.h"
#include "adapters/interfaces/tcp/listener.h"

using namespace lez;

// -----------------------------------------------------------------------

void initialize_logging(const Config& config)
{
    using logging::impl::Boost_logger;

    Boost_logger::Params params;
    params.level = logging::Level_converter::to_level(config.log_level);

    //...

    auto logger = std::make_shared<Boost_logger>(params);
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

        initialize_logging(c);

        logging::trace("trace");
        logging::debug("debug");
        logging::info("info");
        logging::warning("warning");
        logging::error("error");
        logging::fatal("fatal");

        c.log(logging::get_logger(),
              logging::Level::debug);

        /* deps */
        Lua_math math_service;

		// ***

		boost::asio::io_context ioc;
        Listener listener(ioc, math_service, c.port);

		ioc.run();
	}
    catch (const std::exception& ex) {
        std::stringstream sout; sout << "err: " << ex.what();
        logging::error(sout.str());
	}
}
