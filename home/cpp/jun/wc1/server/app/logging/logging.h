#ifndef LOGGING_H
#define LOGGING_H

#include <string>
#include <sstream>
#include <memory>

namespace lez
{
    namespace logging
    {
        enum class Level {
            trace = 0,
            debug,

            info,
            warning,

            error,
            fatal
        };

        class Level_converter
        {
        public:
            static std::string to_str(const Level level);
            static Level to_level(const std::string& str);
        };

        // ---------------------------------------------------------------

        class Logger
        {
        public:
            virtual void to(const std::string& message, Level level) const;

            virtual void trace(const std::string& message) const = 0;
            virtual void debug(const std::string& message) const = 0;

            virtual void info(const std::string& message) const = 0;
            virtual void warning(const std::string& message) const = 0;

            virtual void error(const std::string& message) const = 0;
            virtual void fatal(const std::string& message) const = 0;

        public:
            virtual ~Logger() = default;
        };

        // ---------------------------------------------------------------

        bool is_empty();
        void set_logger(std::shared_ptr<Logger> logger);
        std::shared_ptr<Logger> get_logger();

        // global mt unsafe!?
        // ---------------------------------------------------------------

        void to(const std::string& message, Level level);
        void to(const std::ostringstream& sout, Level level);

        void trace(const std::string& message);
        void debug(const std::string& message);

        void info(const std::string& message);
        void warning(const std::string& message);

        void error(const std::string& message);
        void fatal(const std::string& message);
    }
}

#endif // LOGGING_H
