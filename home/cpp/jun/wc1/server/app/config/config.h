#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>
#include <string>

namespace lez
{
    class Config final
    {
    public:
        static const Config& instance();
        std::string to_string() const;

    public:
        std::uint16_t port;
        std::string log_level;

    private:
        Config();
    };
}

#endif // CONFIG_H
