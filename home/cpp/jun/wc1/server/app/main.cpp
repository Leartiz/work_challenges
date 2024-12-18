#include <memory>
#include <string>
#include <exception>

#include <boost/asio.hpp>

#include "config/config.h"

#include "logging/logging.h"
#include "logging/impl/boost/boost_logger.h"

#include "service/impl/lua_math.h"
#include "adapters/interfaces/tcp/listener.h"

#include "adapters/infrastructure/storage/log/log_storage.h"
#include "adapters/infrastructure/storage/log/impl/clickhouse/clickhouse_storage.h"

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

void test_logging()
{
    logging::trace("trace");
    logging::debug("debug");

    logging::info("info");
    logging::warning("warning");

    logging::error("error");
    logging::fatal("fatal");

    // ***

    logging::trace_f("trace {}", "f");
    logging::debug_f("debug {}", "f");

    logging::info_f("info {}", "f");
    logging::warning_f("warning {}", "f");

    logging::error_f("error {}", "f");
    logging::fatal_f("fatal {}", "f");
}

// -----------------------------------------------------------------------

void run_io_context(boost::asio::io_context& ioc) {
    try {
        ioc.run();
    } catch (const std::exception& e) {

    }
}


int main() /* or wrap in a class: App */ 
{
    using adapters::interfaces::tcp::Listener;
    using service::impl::Lua_math;

    using adapters::infrastructure::Log_storage;
    using adapters::infrastructure::impl::Clickhouse_storage;

	try {

        /* config */

        const auto c = Config::instance();

        /* logger */

        initialize_logging(c);
        test_logging();

        c.log(logging::get_logger(),
              logging::Level::debug);

        // framework!?
        boost::asio::io_context ioc;

        /* services */

        Lua_math math_service;

        /* infrastructure */

        Log_storage *log_storage = new Clickhouse_storage();

        /* interfaces */

        Listener listener(ioc, math_service, c.port);

        // ***

        boost::asio::executor_work_guard<boost::asio::io_context::executor_type> work_guard =
                boost::asio::make_work_guard(ioc);
        const size_t num_threads = std::thread::hardware_concurrency();

        std::vector<std::thread> threads;

        for (size_t i = 0; i < num_threads; ++i) {
            threads.emplace_back(run_io_context, std::ref(ioc));
        }

        for (auto& thread : threads) {
            thread.join();
        }
	}
    catch (const std::exception& ex) {
        std::stringstream sout; sout << "err: " << ex.what();
        logging::error(sout.str());
	}
}
