#include <format>

#include "request.h"
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

        const auto action_name = parse_str_from_json(j, ACTION_JSON_KEY,
                    std::format("missing `{}` in JSON", ACTION_JSON_KEY));

        request.m_service_name = service_name;
        request.m_action_name = action_name;

        // ***

        if (service_name == "math" && action_name == "calculate") { // !
            const auto payload = std::make_shared<math::Payload_with_expr>();
            payload->from_json(j);
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
            j.push_back(m_payload->to_json()); // ?
        }
        else {
            j[Payload::PAYLOAD_JSON_KEY] = nullptr;
        }

        return j;
    }
}
