#include <stdexcept>

#include <nlohmann/json.hpp>

#include "payload_with_expr.h"

namespace lez::adapters::interfaces::tcp::dto::math
{

const std::string& Payload_with_expr::get_expr() const
{
    return m_expression;
}

void Payload_with_expr::set_expr(const std::string& expr)
{
    if (expr.empty()) {
        throw std::runtime_error("expression is empty");
    }

    m_expression = expr;
}

const nlohmann::json Payload_with_expr::to_json() const
{
    using nlohmann::json;
    const json payload = { { EXPRESSION_JSON_KEY, m_expression } };
    return json { { PAYLOAD_JSON_KEY, payload } };
}

void Payload_with_expr::from_json(const nlohmann::json& j)
{
    if (j.contains(PAYLOAD_JSON_KEY) &&
        j[PAYLOAD_JSON_KEY].contains(EXPRESSION_JSON_KEY)) {

        m_expression = j[PAYLOAD_JSON_KEY][EXPRESSION_JSON_KEY]
            .get<std::string>();
    }
    else {
        throw std::runtime_error(
            std::format("missing `{}` or `{}` in JSON",
                        PAYLOAD_JSON_KEY, EXPRESSION_JSON_KEY));
    }
}

}

