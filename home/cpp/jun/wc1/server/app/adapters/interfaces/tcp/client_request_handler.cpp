#include "client_request_handler.h"

namespace lez::adapters::interfaces::tcp
{
    Client_request_handler::Client_request_handler(const std::string& client_id,
                                     const service::Services& services)
        : m_client_id{ client_id }
        , m_services{ services }
    {}

    dto::Sp_response Client_request_handler::handle(dto::Sp_request r)
    {
        return {};
    }
}
