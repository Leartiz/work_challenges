#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <cstdint>
#include <memory>

#include <nlohmann/json.hpp>

#include "request_payload.h"

namespace lez::adapters::interfaces::tcp::dto
{
    class Request final
    {
        friend class std::shared_ptr<Request>;

    public:
        using Sp = std::shared_ptr<Request>;

    public:
        struct Json_key final
        {
            static constexpr char ID[]      = "request_id";
            static constexpr char SERVICE[] = "service";
            static constexpr char ACTION[]  = "action";
        };

    public:
        // creates the desired type!
        static std::shared_ptr<Request> from_json(const nlohmann::json&);
        const nlohmann::json to_json() const;

    public:
        Request();
        void set_payload(Sp_req_payload);

        void set_service_name(const std::string&);
        void set_action_name(const std::string&);

        std::uint64_t get_id() const;
        const std::string& get_service_name() const;
        const std::string& get_action_name() const;
        Sp_req_payload get_payload() const;

    private:
        std::uint64_t m_id;
        std::string m_service_name;
        std::string m_action_name;

    private:
        Sp_req_payload m_payload;
    };

    using Sp_request = Request::Sp;
}

#endif // REQUEST_H
