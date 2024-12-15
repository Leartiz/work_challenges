#ifndef PAYLOAD_WITH_EXPR_H
#define PAYLOAD_WITH_EXPR_H

#include <nlohmann/json.hpp>

#include "../payload.h"

namespace lez::adapters::interfaces::tcp::dto::math
{

class Payload_with_expr : public Payload
{
public:
    static constexpr char EXPRESSION_JSON_KEY[] = "expression";

public:
    ~Payload_with_expr() override = default;

public:
    const std::string& get_expr() const;
    void set_expr(const std::string&);

    // Payload interface
public:
    const nlohmann::json to_json() const override;
    void from_json(const nlohmann::json&) override;

private:
    std::string m_expression;
};

}

#endif // PAYLOAD_WITH_EXPR_H
