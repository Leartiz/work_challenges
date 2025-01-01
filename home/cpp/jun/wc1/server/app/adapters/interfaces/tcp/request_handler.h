#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <map>
#include <string>
#include <functional>

#include "dto/response.h"
#include "request_context.h"
#include "service/services.h"

namespace lez::adapters::interfaces::tcp
{
    class Request_handler final
    {
    public:
        explicit Request_handler(const service::Services&);

    public:
        dto::Response::Sp handle(Request_context::Sp ctx);

        // services/use-cases!
    private:
        const service::Services m_services; // as ptrs!

    private:
        using route_handler = std::function<dto::Response::Sp(Request_context::Sp ctx)>;
        using route_map = std::map<std::string, std::map<std::string, route_handler>>;
        route_map m_route_map;
    };
}

#endif // REQUEST_HANDLER_H
