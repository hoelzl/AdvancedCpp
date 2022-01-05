#include "variants.hpp"

#include <iostream>

namespace variants {

std::string compile_node(const Node& node)
{
    if (std::holds_alternative<Statement>(node)) {
        const auto statement = std::get<Statement>(node);
        return "Compiling statement " + statement.sub_statement();
    }
    else if (std::holds_alternative<Expression>(node)) {
        const auto expression = std::get<Expression>(node);
        return "Compiling expression " + expression.sub_expressions();
    }
    else {
        const auto comment = std::get<Comment>(node);
        return "Skipping comment '" + comment.text() + "'";
    }
}

std::string compile_node_2_dispatch(const Statement& statement)
{
    return "Compiling statement " + statement.sub_statement();
}

std::string compile_node_2_dispatch(const Expression& expression)
{
    return "Compiling expression " + expression.sub_expressions();
}

std::string compile_node_2_dispatch(const Comment& comment)
{
    return "Skipping comment '" + comment.text() + "'";
}

std::string compile_node_2(const Node& node)
{
    return std::visit([](auto n) { return compile_node_2_dispatch(n); }, node);
}

std::string compile_node_3(const Node& node)
{
    return std::visit(
        overloaded{
            [](const Statement& s) {
                return "Compiling statement " + s.sub_statement();
            },
            [](const Expression& e) {
                return "Compiling expression " + e.sub_expressions();
            },
            [](const Comment& c) { return "Skipping comment '" + c.text() + "'"; }},
        node);
}


} // namespace variants
