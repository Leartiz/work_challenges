#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <string>

#include "dto/request.h"
#include "service/math_service.h"

namespace lez::adapters::interfaces::tcp
{
    using namespace service::contract;

    // ***

    class Request_handler final
    {
    public:
        Request_handler(
            Math_service& math_service);

    public:
        void handle(const std::string& client_id, dto::Sp_request r);

        // services/use-cases!
    private:
        Math_service& m_math_service;
    };
}

#endif // REQUEST_HANDLER_H
