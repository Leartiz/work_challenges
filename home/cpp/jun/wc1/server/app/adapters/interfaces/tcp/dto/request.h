#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <cstdint>
#include <memory>

#include <nlohmann/json.hpp>

#include "payload.h"

namespace lez::adapters::interfaces::tcp::dto
{
    class Request final
    {
        friend class std::shared_ptr<Request>;

    public:
        static constexpr char ID_JSON_KEY[] = "request_id";
        static constexpr char SERVICE_JSON_KEY[] = "service";
        static constexpr char ACTION_JSON_KEY[] = "action";

    public:
        static std::shared_ptr<Request> from_json(const nlohmann::json&);
        const nlohmann::json to_json() const;

    public:
        Request();
        void set_payload(std::shared_ptr<Payload>);
        void set_service_name(const std::string&);
        void set_action_name(const std::string&);

    private:
        std::uint64_t m_id;
        std::string m_service_name;
        std::string m_action_name;

    private:
        std::shared_ptr<Payload> m_payload;
    };
}

#endif // REQUEST_H
