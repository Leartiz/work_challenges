#include <memory>

#include "request_handler.h"
#include "service/services.h"

#include "dto/math/req_payload_with_expr.h"
#include "dto/math/res_result_with_double.h"

namespace lez::adapters::interfaces::tcp
{
    using namespace service::contract;

    Request_handler::Request_handler(const service::Services& services)
        : m_services{ services }
    {
        m_route_map[Math_service::SERVICE_NAME][Math_service::Action::CALCULATE] =
            [this](Request_context::Sp ctx) -> dto::Response::Sp {

            auto r = ctx->req();
            auto pd = r->get_payload();

            if (!pd) {
                return dto::Response::bad_request(
                    r->get_id(), "payload is nullptr");
            }

            using namespace dto::math;
            auto cpd = std::dynamic_pointer_cast<Req_payload_with_expr>(pd);
            if (!cpd) {
                return dto::Response::bad_request(
                    r->get_id(), "payload is of a different type");
            }

            // ***

            const auto value = m_services.math_service->calculate_expression(cpd->get_expr());
            return dto::Response::sucess(r->get_id(), nullptr);
        };
        //...
    }

    dto::Response::Sp Request_handler::handle(Request_context::Sp ctx)
    {
        auto r = ctx->req();

        const auto& action = r->get_action_name();
        const auto& service = r->get_service_name();

        if (!m_route_map.contains(service)) {

        }
        if (!m_route_map[service].contains(action)) {

        }

        return m_route_map[service][action](ctx);
    }
}
