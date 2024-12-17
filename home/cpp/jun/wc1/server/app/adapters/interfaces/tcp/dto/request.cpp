#include <format>

#include "request.h"
#include "common_validator.h"
#include "math/payload_with_expr.h"

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

    void Request::set_payload(std::shared_ptr<Payload> pd)
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
        if (j.contains(ID_JSON_KEY)) {
            request.m_id = j[ID_JSON_KEY].get<std::uint64_t>();
        }
        else {
            throw std::runtime_error(std::format("missing `{}` in JSON", ID_JSON_KEY));
        }

        // ***

        const auto service_name = parse_str_from_json(j, SERVICE_JSON_KEY,
                    std::format("missing `{}` in JSON", SERVICE_JSON_KEY));
        Common_validator::string_not_empty(service_name,
                    std::format("`{}` is empty string", SERVICE_JSON_KEY));

        const auto action_name = parse_str_from_json(j, ACTION_JSON_KEY,
                    std::format("missing `{}` in JSON", ACTION_JSON_KEY));
        Common_validator::string_not_empty(action_name,
                    std::format("`{}` is empty string", ACTION_JSON_KEY));

        request.m_service_name = service_name;
        request.m_action_name = action_name;

        // ***

        if (service_name == "math" && action_name == "calculate") { // !
            const auto payload = std::make_shared<math::Payload_with_expr>();
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
        j[ID_JSON_KEY] = m_id;
        j[SERVICE_JSON_KEY] = m_service_name;
        j[ACTION_JSON_KEY] = m_action_name;

        if (m_payload) {
           auto j_payload = m_payload->to_json(); // ?
           for (auto& element : j_payload.items()) {
               j[element.key()] = element.value();
           }
        }
        else {
            j[Payload::PAYLOAD_JSON_KEY] = nullptr;
        }

        return j;
    }
}
