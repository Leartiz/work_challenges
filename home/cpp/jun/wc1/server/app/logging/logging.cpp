#include <mutex>
#include <stdexcept>

#include "logging.h"

namespace lez
{
    namespace logging
    {
        std::mutex mx;
        std::shared_ptr<Logger> global_logger = nullptr;

        // ---------------------------------------------------------------

        bool is_empty()
        {
            std::lock_guard<std::mutex> _{ mx };
            return global_logger == nullptr;
        }

        void set_logger(std::shared_ptr<Logger> logger)
        {
            if (!is_empty()) {
                throw std::runtime_error{ "global logger already set" };
            }
            if (!logger) {
                throw std::runtime_error{ "logger is nullptr" };
            }

            // ***

            std::lock_guard<std::mutex> _{ mx };
            global_logger = logger;
        }

        std::shared_ptr<Logger> get_logger()
        {
            std::lock_guard<std::mutex> _{ mx };
            return global_logger;
        }

        // ---------------------------------------------------------------

        void trace(const std::string& message)
        {
            // no nullptr check!?

            global_logger->trace(message);

            // cppcheck reports unused variable!?
            static_cast<void>(message);
        }

        void debug(const std::string& message)
        {
            global_logger->debug(message);
        }

        void info(const std::string& message)
        {
            global_logger->info(message);
        }

        void warning(const std::string& message)
        {
            global_logger->warning(message);
        }

        void error(const std::string& message)
        {
            global_logger->error(message);
        }

        void fatal(const std::string& message)
        {
            global_logger->fatal(message);
        }
    }
}
