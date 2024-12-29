#ifndef CLIENT_REQUEST_HANDLER_H
#define CLIENT_REQUEST_HANDLER_H

#include <string>

#include "dto/request.h"
#include "dto/response.h"
#include "service/services.h"

namespace lez::adapters::interfaces::tcp
{
    class Client_request_handler final
    {
    public:
        Client_request_handler(const std::string& client_id,
                               const service::Services&);

    public:
        dto::Sp_response handle(dto::Sp_request r);

        // services/use-cases!
    private:
        const std::string m_client_id;
        const service::Services m_services; // as ptrs!
    };
}

#endif // CLIENT_REQUEST_HANDLER_H
