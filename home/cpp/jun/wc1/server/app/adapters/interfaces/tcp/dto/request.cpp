#include <format>

#include "request.h"
#include "common_validator.h"
#include "math/req_payload_with_expr.h"

namespace
{
    std::string parse_str_from_json(const nlohmann::json& j, const std::string& key,
                                    const std::string& err_message)
    {
        if (j.contains(key)) {
            return j[key].get<std::string>();
        }
        throw std::runtime_error(err_message);
    }
}

// -----------------------------------------------------------------------

namespace lez::adapters::interfaces::tcp::dto
{

    Request::Request()
        : m_id{ 0 }
        , m_service_name{}
        , m_action_name{}
        , m_payload{ nullptr }
    {}

// -----------------------------------------------------------------------

    void Request::set_payload(Sp_req_payload pd)
    {
        m_payload = pd;
    }

    void Request::set_service_name(const std::string& str)
    {
        Common_validator::string_not_empty(str, "service name cannot be empty");
        m_service_name = str;
    }

    void Request::set_action_name(const std::string& str)
    {
        Common_validator::string_not_empty(str, "action name cannot be empty");
        m_action_name = str;
    }

// -----------------------------------------------------------------------

    std::shared_ptr<Request> Request::from_json(const nlohmann::json& j)
    {
        Request request;
        if (j.contains(Json_key::ID)) {
            request.m_id = j[Json_key::ID].get<std::uint64_t>();
        }
        else {
            throw std::runtime_error(
                std::format("missing `{}` in JSON", Json_key::ID));
        }

        // ***

        const auto service_name = parse_str_from_json(j, Json_key::SERVICE,
                    std::format("missing `{}` in JSON", Json_key::SERVICE));
        Common_validator::string_not_empty(service_name,
                    std::format("`{}` is empty string", Json_key::SERVICE));

        const auto action_name = parse_str_from_json(j, Json_key::ACTION,
                    std::format("missing `{}` in JSON", Json_key::ACTION));
        Common_validator::string_not_empty(action_name,
                    std::format("`{}` is empty string", Json_key::ACTION));

        request.m_service_name = service_name;
        request.m_action_name = action_name;

        // ***

        if (service_name == "math" && action_name == "calculate") { // !
            const auto payload = std::make_shared<math::Req_payload_with_expr>();
            payload->from_json(j); // void!
            request.m_payload = payload;
        }
        //...
        else {
            throw std::runtime_error("unsupported service or action");
        }

        return std::make_shared<Request>(request);
    }

    /*
        ```json
        {
            "request_id": "<uint64>",

            "service": "math",
            "action": "calculate",

            "payload": {
                "expression": "<string>"
            }
        }
        ```
    */
    const nlohmann::json Request::to_json() const
    {
        nlohmann::json j;
        j[Json_key::ID] = m_id;
        j[Json_key::SERVICE] = m_service_name;
        j[Json_key::ACTION] = m_action_name;

        if (m_payload) {
           auto j_payload = m_payload->to_json(); // ?
           for (auto& element : j_payload.items()) {
               j[element.key()] = element.value();
           }
        }
        else {
            j[Request_payload::Json_key::PAYLOAD] = nullptr; // !
        }

        return j;
    }
}
