#include "variants.hpp"

#include <iostream>

namespace variants {

std::string compile_node(Node const& node)
{
    if (std::holds_alternative<Statement>(node)) {
        auto const statement = std::get<Statement>(node);
        return "Compiling statement " + statement.sub_statement();
    }
    else if (std::holds_alternative<Expression>(node)) {
        auto const expression = std::get<Expression>(node);
        return "Compiling expression " + expression.sub_expressions();
    }
    else {
        auto const comment = std::get<Comment>(node);
        return "Skipping comment '" + comment.text() + "'";
    }
}

std::string compile_node_2_dispatch(Statement const& statement)
{
    return "Compiling statement " + statement.sub_statement();
}

std::string compile_node_2_dispatch(Expression const& expression)
{
    return "Compiling expression " + expression.sub_expressions();
}

std::string compile_node_2_dispatch(Comment const& comment)
{
    return "Skipping comment '" + comment.text() + "'";
}

std::string compile_node_2(Node const& node)
{
    return std::visit([](auto n) { return compile_node_2_dispatch(n); }, node);
}

std::string compile_node_3(Node const& node)
{
    return std::visit(
        overloaded{
            [](Statement const& s) {
                return "Compiling statement " + s.sub_statement();
            },
            [](Expression const& e) {
                return "Compiling expression " + e.sub_expressions();
            },
            [](Comment const& c) { return "Skipping comment '" + c.text() + "'"; }},
        node);
}


} // namespace variants
