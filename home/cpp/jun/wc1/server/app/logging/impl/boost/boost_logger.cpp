#include <sstream>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include "boost_logger.h"

namespace lez
{
    namespace logging
    {
        namespace
        {
            using boost::log::trivial::severity_level;

            severity_level convert_level(const Level level)
            {
                switch (level) {
                case Level::trace: return severity_level::trace;
                case Level::debug: return severity_level::debug;

                case Level::info: return severity_level::info;
                case Level::warning: return severity_level::warning;

                case Level::error: return severity_level::error;
                case Level::fatal: return severity_level::fatal;
                }
            }
        }

        namespace impl
        {
            Boost_logger::Params::Params()
                : enable_file(true), dir_name("logs"), file_name("actions")
                , rotation_size(5 * 1024 * 1024), max_files(5)
                , level(Level::trace) {}

            // -----------------------------------------------------------

            Boost_logger::Boost_logger(const Params& options)
            {
                const std::string format =
                    "[%TimeStamp%] [%Severity%]\t[%ThreadID%]: %Message%";

                boost::log::add_console_log(
                    std::cout, boost::log::keywords::format = format); // ?

                if (options.enable_file) {
                    std::ostringstream full_file_name;
                    full_file_name << options.dir_name << "/"
                                   << options.file_name << "_%N.log";

                    auto file_sink = boost::log::add_file_log(
                        boost::log::keywords::open_mode = std::ios::app,
                        boost::log::keywords::file_name = full_file_name.str(),
                        boost::log::keywords::rotation_size = options.rotation_size,
                        boost::log::keywords::max_files = options.max_files,
                        boost::log::keywords::format = format);
                    file_sink->locked_backend()->auto_flush(); // !
                }

                // ***

                boost::log::add_common_attributes();

                boost::log::core::get()->set_filter(
                    boost::log::trivial::severity >= convert_level(options.level));
            }

            // -----------------------------------------------------------

            void Boost_logger::trace(const std::string& message)
            {
                BOOST_LOG_TRIVIAL(trace) << message;
            }

            void Boost_logger::debug(const std::string& message)
            {
                BOOST_LOG_TRIVIAL(debug) << message;
            }

            void Boost_logger::info(const std::string& message)
            {
                BOOST_LOG_TRIVIAL(info) << message;
            }

            void Boost_logger::warning(const std::string& message)
            {
                BOOST_LOG_TRIVIAL(warning) << message;
            }

            void Boost_logger::error(const std::string& message)
            {
                BOOST_LOG_TRIVIAL(error) << message;
            }

            void Boost_logger::fatal(const std::string& message)
            {
                BOOST_LOG_TRIVIAL(fatal) << message;
            }

            Boost_logger::~Boost_logger() {}
        }
    }
}
