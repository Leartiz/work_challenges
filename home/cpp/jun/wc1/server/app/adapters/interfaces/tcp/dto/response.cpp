#include <stdexcept>

#include "response.h"

namespace lez::adapters::interfaces::tcp::dto
{
    const nlohmann::json Response::Metadata::to_json() const
    {
        nlohmann::json j; // object!
        j[Json_key::DURATION] = duration;
        j[Json_key::TIMESTAMP] = timestamp;
        return j;
    }

    const nlohmann::json Response::Error::to_json() const
    {
        nlohmann::json j;
        j[Json_key::MESSAGE] = message;
        return j;
    }

    // -------------------------------------------------------------------

    Response::Response(std::uint64_t id, int status_code, std::shared_ptr<Error> err)
        : m_request_id{ id }, m_status_code{ status_code }
        , m_error{ err }, m_result{ nullptr }
        , m_metadata{ nullptr }
    {
        if (!m_error)
            throw std::invalid_argument{ "error is nullptr" };

        // TODO: combinations check?
    }

    Response::Response(std::uint64_t id, int status_code, std::shared_ptr<Response_result> rr)
        : m_request_id{ id }, m_status_code{ status_code }
        , m_error{ nullptr }, m_result{ rr }
        , m_metadata{ nullptr }
    {
        if (!m_result)
            throw std::invalid_argument{ "result is nullptr" };
    }

    void Response::set_metadata(std::shared_ptr<Metadata> metadata)
    {
        m_metadata = metadata;
    }

    // -------------------------------------------------------------------

    const nlohmann::json Response::to_json() const
    {
        nlohmann::json j;
        j[Json_key::REQUEST_ID] = m_request_id;
        j[Json_key::STATUS_CODE] = m_status_code;

        j[Json_key::METADATA] = nullptr;
        j[Json_key::RESULT] = nullptr;
        j[Json_key::ERR] = nullptr;

        if (m_metadata) {
            j[Json_key::METADATA] = m_metadata->to_json();
        }

        // or
        if (m_error) {
            j[Json_key::ERR] = m_error->to_json();
        }
        else {
            j[Json_key::RESULT] = m_result->to_json();
        }

        return j;
    }
}
