#ifndef BOOST_LOGGER_H
#define BOOST_LOGGER_H

#include <string>

#include "logging/logging.h"

namespace lez
{
    namespace logging
    {
        namespace impl
        {
            class Boost_logger final : public Logger
            {
            public:
                struct Params final
                {
                public:
                    Params();

                public:
                    bool enable_file;
                    std::string dir_name;
                    std::string file_name;

                    size_t rotation_size;
                    size_t max_files;

                    Level level;
                };

            public:
                explicit Boost_logger(const Params&);

            public:
                void trace(const std::string& message) override;
                void debug(const std::string& message) override;

                void info(const std::string& message) override;
                void warning(const std::string& message) override;

                void error(const std::string& message) override;
                void fatal(const std::string& message) override;

            public:
                ~Boost_logger() override;
            };
        }
    }
}

#endif // BOOST_LOGGER_H
