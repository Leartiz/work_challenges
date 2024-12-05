#ifndef LOGGING_H
#define LOGGING_H

#include <string>
#include <memory>

namespace lez
{
    namespace logging
    {
        enum class Level
        {
            trace = 0,
            debug,

            info,
            warning,

            error,
            fatal
        };

        // ---------------------------------------------------------------

        class Logger
        {
        public:
            virtual void trace(const std::string& message) = 0;
            virtual void debug(const std::string& message) = 0;

            virtual void info(const std::string& message) = 0;
            virtual void warning(const std::string& message) = 0;

            virtual void error(const std::string& message) = 0;
            virtual void fatal(const std::string& message) = 0;

        public:
            virtual ~Logger() = default;
        };

        // ---------------------------------------------------------------

        bool is_empty();
        void set_logger(std::shared_ptr<Logger> logger);
        std::shared_ptr<Logger> get_logger();

        // global mt unsafe!?
        // ---------------------------------------------------------------

        void trace(const std::string& message);
        void debug(const std::string& message);

        void info(const std::string& message);
        void warning(const std::string& message);

        void error(const std::string& message);
        void fatal(const std::string& message);
    }
}

#endif // LOGGING_H
