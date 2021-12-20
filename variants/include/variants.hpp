#pragma once
#ifndef VARIANTS_VARIANTS_HPP
#define VARIANTS_VARIANTS_HPP

#include <string>
#include <utility>
#include <variant>

namespace variants {

// Types for a compiler AST, not using inheritance.

class Statement
{
public:
    explicit Statement(std::string statement) : sub_statements_{std::move(statement)} {}

    [[nodiscard]] std::string sub_statement() const { return sub_statements_; }
    void sub_statement(std::string const& statement) { sub_statements_ = statement; }

private:
    std::string sub_statements_{};
};

class Expression
{
public:
    explicit Expression(std::string exprs) : subexpressions_{std::move(exprs)} {}

    [[nodiscard]] std::string sub_expressions() const { return subexpressions_; }
    void sub_expressions(std::string const& exprs) { subexpressions_ = exprs; }

private:
    std::string subexpressions_{};
};

class Comment
{
public:
    explicit Comment(std::string text) : text_{std::move(text)} {}

    [[nodiscard]] std::string text() const { return text_; }

private:
    std::string text_{};
};

// Node is a variant of all possible AST elements.

using Node = ::std::variant<Statement, Expression, Comment>;

// We can  define a function using explicit checks with holds_alternative() to find the
// stored type and get<>() calls to extract it.

std::string compile_node(Node const& node);

// If we have an overload set that can accept all members of the variant, we can also
// use visit() to avoid explicit dispatching:

std::string compile_node_2_dispatch(Statement const& statement);
std::string compile_node_2_dispatch(Expression const& expression);
std::string compile_node_2_dispatch(Comment const& comment);

std::string compile_node_2(Node const& node);

// Or we can define our own "pattern matching" (modeled after Stroustrup's "overloaded"
// in "A Tour of C++":

template <typename... Ts>
struct overloaded : Ts...
{
    using Ts::operator()...;
};

// Deduction guide
// ReSharper disable once CppMissingSpace
template <typename... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

std::string compile_node_3(Node const& node);

} // namespace variants

#endif // VARIANTS_VARIANTS_HPP
