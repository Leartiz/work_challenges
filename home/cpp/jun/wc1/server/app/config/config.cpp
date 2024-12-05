#include <sstream>

#include "config.h"

#include "laserpants/dotenv/dotenv.h"

namespace lez
{
    const Config& Config::instance()
    {
        static Config c;
        return c;
    }

    // -------------------------------------------------------------------

    Config::Config()
    {
        dotenv::init();

        const std::string port_str = dotenv::getenv("PORT");
        if (!port_str.empty()) {
            port = static_cast<std::uint16_t>(std::stoi(port_str));
        } else {
            port = 24444;
        }

        const std::string log_level_str = dotenv::getenv("LOG_LEVEL");
        if (!log_level_str.empty()) {
            log_level = log_level_str;
        } else {
            log_level = "trace";
        }
    }

    std::string Config::to_string() const
    {
        std::ostringstream sout;
        sout << "PORT: " << port << " | ";
        sout << "LOG_LEVE: " << log_level;
        return sout.str();
    }
}


