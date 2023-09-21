#include <iostream>
#include <functional>

#include <boost/thread/thread.hpp>
#include <boost/thread/barrier.hpp>

#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sinks.hpp>

// it is possible in another way...
#include <boost/date_time/posix_time/posix_time.hpp>

// -----------------------------------------------------------------------

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

// -----------------------------------------------------------------------

void init_sync_log()
{
    typedef sinks::text_file_backend back;
    typedef sinks::synchronous_sink<back> file_sync_sink;

    // ***

    boost::shared_ptr<file_sync_sink> sink(
        new file_sync_sink(
            boost::make_shared<back>(),

            keywords::target_file_name = "%d%m%Y_%H%M%S_#%5N.log",
            keywords::file_name = "temp.log",                      // then renamed and moved... to target.
            keywords::rotation_size = 1024 * 10                    // 10 KB
        )
    );

    // ***

    sink.get()->locked_backend()->set_file_collector(
        sinks::file::make_collector(
            keywords::target = "logs",
            keywords::max_files = 6
        )
    );

    sink->set_formatter(
        expr::format("#%1% | %2% | %3% : %4%")
            % expr::attr<unsigned int>("RecID")
            % expr::attr<boost::posix_time::ptime>("Stamp")
            % expr::attr<logging::trivial::severity_level>("Severity") // permanent literal?
            % expr::smessage
    );

    sink->locked_backend()->scan_for_files();

    // ***

    logging::core::get()->add_sink(sink);

    logging::core::get()->add_global_attribute("Stamp", attrs::local_clock());
    logging::core::get()->add_global_attribute("RecID", attrs::counter<unsigned int>());
}

void th_func(boost::barrier& bar)
{
    bar.wait();

    for (unsigned int i = 0; i < 1000; ++i) {
        BOOST_LOG_TRIVIAL(severity_level::info) << "record #" << std::to_string(i);
    }
}

int main(int, char*[])
{
    init_sync_log();

    // *** test

    const int tcount = 10;
    boost::barrier bar(tcount);

    boost::thread_group tg;
    for (int i = 0; i < tcount; ++i) {
        tg.create_thread(std::bind(th_func, std::ref(bar)));
    }
    tg.join_all();

    // ***

    std::cout << "[END]" << std::endl;
    return 0;
}
