#ifndef REQUEST_CONTEXT_H
#define REQUEST_CONTEXT_H

#include <memory>

#include "dto/request.h"
#include "client_context.h"

namespace lez::adapters::interfaces::tcp
{
    class Request_context
    {
    public:
        using Sp = std::shared_ptr<Request_context>;
        static Sp create(Client_context::Sp client_ctx, dto::Sp_request req);

    public:
        Request_context(Client_context::Sp client_ctx, dto::Sp_request req);
        Client_context::Sp client_ctx() const;
        dto::Sp_request req() const;

    private:
        Client_context::Sp m_client_ctx;
        dto::Sp_request m_request;
    };
}

#endif // REQUEST_CONTEXT_H
