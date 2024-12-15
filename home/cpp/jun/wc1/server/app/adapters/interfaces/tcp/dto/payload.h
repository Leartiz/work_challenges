#ifndef PAYLOAD_H
#define PAYLOAD_H

#include "nlohmann/json.hpp"

namespace lez::adapters::interfaces::tcp::dto
{
    class Payload
    {
    public:
        static constexpr char PAYLOAD_JSON_KEY[] = "payload";

    public:
        virtual ~Payload() = default;

    public:
        virtual const nlohmann::json to_json() const = 0;
        virtual void from_json(const nlohmann::json& json) = 0;
    };
}

#endif // PAYLOAD_H
