#include "variants.hpp"

#include "catch2/catch_test_macros.hpp"

using namespace variants;

TEST_CASE("compile_node()")
{
    auto statement = Statement{"x += 2;"};
    auto expression = Expression{"2 * x + 1"};
    auto comment = Comment{"What does this do?"};

    SECTION("Compile statement")
    {
        CHECK(compile_node(Node{statement}) == "Compiling statement x += 2;");
    }

    SECTION("Compile expression")
    {
        CHECK(compile_node(Node{expression}) == "Compiling expression 2 * x + 1");
    }

    SECTION("Compile comment")
    {
        CHECK(compile_node(Node{comment}) == "Skipping comment 'What does this do?'");
    }
}

TEST_CASE("compile_node_2()")
{
    auto statement = Statement{"x += 2;"};
    auto expression = Expression{"2 * x + 1"};
    auto comment = Comment{"What does this do?"};

    SECTION("Compile statement")
    {
        CHECK(compile_node_2(Node{statement}) == "Compiling statement x += 2;");
    }

    SECTION("Compile expression")
    {
        CHECK(compile_node_2(Node{expression}) == "Compiling expression 2 * x + 1");
    }

    SECTION("Compile comment")
    {
        CHECK(compile_node_2(Node{comment}) == "Skipping comment 'What does this do?'");
    }
}

TEST_CASE("compile_node_3()")
{
    auto statement = Statement{"x += 2;"};
    auto expression = Expression{"2 * x + 1"};
    auto comment = Comment{"What does this do?"};

    SECTION("Compile statement")
    {
        CHECK(compile_node_3(Node{statement}) == "Compiling statement x += 2;");
    }

    SECTION("Compile expression")
    {
        CHECK(compile_node_3(Node{expression}) == "Compiling expression 2 * x + 1");
    }

    SECTION("Compile comment")
    {
        CHECK(compile_node_3(Node{comment}) == "Skipping comment 'What does this do?'");
    }
}
