#include "class_templates.hpp"

#include <deque>
#include <catch2/catch_test_macros.hpp>
#include <string>

using namespace templates;
using namespace std::literals::string_literals;

TEST_CASE("Stack<int> V1")
{
    Stack<int> stack{};

    SECTION("Stack operations.")
    {
        CHECK(stack.empty());
        CHECK_THROWS_AS(stack.pop(), std::logic_error);
        CHECK_THROWS_AS(stack.top(), std::logic_error);
        CHECK_NOTHROW(stack.push(123));
        CHECK_FALSE(stack.empty());
        CHECK(stack.top() == 123);
        CHECK_NOTHROW(stack.pop());
        CHECK(stack.empty());
    }

    SECTION("Push has a default argument.")
    {
        stack.push();
        CHECK(stack.top() == 0);
    }

    SECTION("Default stack is of type Stack<int>.")
    {
        CHECK(std::is_same_v<decltype(Stack<int>::default_stack), Stack<int>>);
    }

    SECTION("Default stack can be used.")
    {
        CHECK(Stack<int>::default_stack.empty());
        CHECK_THROWS_AS(Stack<int>::default_stack.pop(), std::logic_error);
        CHECK_THROWS_AS(Stack<int>::default_stack.top(), std::logic_error);
        CHECK_NOTHROW(Stack<int>::default_stack.push(123));
        CHECK_FALSE(Stack<int>::default_stack.empty());
        CHECK(Stack<int>::default_stack.top() == 123);
        CHECK_NOTHROW(Stack<int>::default_stack.pop());
        CHECK(Stack<int>::default_stack.empty());
    }
}

TEST_CASE("Stack<std::string> V1")
{
    Stack<std::string> stack{};

    SECTION("Stack operations.")
    {
        CHECK(stack.empty());
        CHECK_THROWS_AS(stack.pop(), std::logic_error);
        CHECK_THROWS_AS(stack.top(), std::logic_error);
        CHECK_NOTHROW(stack.push("foo"s));
        CHECK_FALSE(stack.empty());
        CHECK(stack.top() == "foo"s);
        CHECK_NOTHROW(stack.pop());
        CHECK(stack.empty());
    }

    SECTION("Push has a default argument.")
    {
        stack.push();
        CHECK(stack.top() == ""s);
    }


    SECTION("Default stack can be used for string as well.")
    {
        CHECK(Stack<std::string>::default_stack.empty());
        CHECK_THROWS_AS(Stack<std::string>::default_stack.pop(), std::logic_error);
        CHECK_THROWS_AS(Stack<std::string>::default_stack.top(), std::logic_error);
        Stack<std::string>::default_stack.push("a value"s);
        CHECK_FALSE(Stack<std::string>::default_stack.empty());
        CHECK(Stack<std::string>::default_stack.top() == "a value"s);
        Stack<std::string>::default_stack.pop();
        CHECK(Stack<std::string>::default_stack.empty());
    }
}

TEST_CASE("Stack<IntWrapper>")
{
    Stack<IntWrapper> stack{};

    SECTION("Stack operations.")
    {
        CHECK(stack.empty());
        CHECK_NOTHROW(stack.pop());
        CHECK(stack.top() == IntWrapper{0});
        CHECK_NOTHROW(stack.push(IntWrapper{2}));
        CHECK_FALSE(stack.empty());
        CHECK(stack.top() == IntWrapper{2});
        CHECK_NOTHROW(stack.pop());
        CHECK(stack.empty());
    }

    SECTION("Push has a default argument.")
    {
        stack.push();
        CHECK(stack.top() == IntWrapper{0});
    }
}

TEST_CASE("Stack<int*>")
{
    Stack<int*> stack{};
    int i{1};
    int* pi{&i};

    SECTION("Stack operations.")
    {
        CHECK(stack.empty());
        CHECK_THROWS_AS(stack.pop(), std::logic_error);
        CHECK_THROWS_AS(stack.top(), std::logic_error);
        CHECK_NOTHROW(stack.push(pi));
        CHECK_FALSE(stack.empty());
        CHECK(stack.top() == pi);
        CHECK(stack.pop() == pi);
        CHECK(stack.empty());
    }
}

TEST_CASE("Multiple Specializations")
{
    CHECK(MyClass<int, double>::info() == "<T1, T2>");
    CHECK(MyClass<double, double>::info() == "<T, T>");
    CHECK(MyClass<double, int>::info() == "<T, int>");
    CHECK(MyClass<double*, int*>::info() == "<T1*, T2*>");
    // Ambiguous, could be <T, T> or <T1*, T2*>
    // CHECK(MyClass<double*, double*>::info() == "<T1*, T2*>");
    // Ambiguous, could be <T, T> or <T, int>
    // CHECK(MyClass<int, int>::info() == "???");
}

TEST_CASE("StackV2<int>")
{
    StackV2<int> stack{};

    SECTION("Stack operations.")
    {
        CHECK(stack.empty());
        CHECK_THROWS_AS(stack.pop(), std::logic_error);
        CHECK_THROWS_AS(stack.top(), std::logic_error);
        CHECK_NOTHROW(stack.push(123));
        CHECK_FALSE(stack.empty());
        CHECK(stack.top() == 123);
        CHECK_NOTHROW(stack.pop());
        CHECK(stack.empty());
    }
}


TEST_CASE("StackV2<int, std::deque<int>>")
{
    StackV2<int, std::deque<int>> stack{};

    SECTION("Stack operations.")
    {
        CHECK(stack.empty());
        CHECK_THROWS_AS(stack.pop(), std::logic_error);
        CHECK_THROWS_AS(stack.top(), std::logic_error);
        CHECK_NOTHROW(stack.push(123));
        CHECK_FALSE(stack.empty());
        CHECK(stack.top() == 123);
        CHECK_NOTHROW(stack.pop());
        CHECK(stack.empty());
    }
}


TEST_CASE("StackV2 (deduced)")
{
    StackV2 stack{1};

    SECTION("Stack operations.")
    {
        CHECK_FALSE(stack.empty());
        CHECK(stack.top() == 1);
        CHECK_NOTHROW(stack.pop());
        CHECK_NOTHROW(stack.push(123));
        CHECK_FALSE(stack.empty());
        CHECK(stack.top() == 123);
        CHECK_NOTHROW(stack.pop());
        CHECK(stack.empty());
    }
}

TEST_CASE("StackV2 (deduction guidelines)")
{
    // Oops. Reference argument, therefore no decay.
    // Without deduction guides, type is deduced to const char[6].
    StackV2 stack{"Hello"};

    SECTION("Stack operations.")
    {
        CHECK_FALSE(stack.empty());
        CHECK(stack.top() == "Hello");
        // Cannot put a const char[7] on a Stack<const char[6]>
        CHECK_NOTHROW(stack.push("World!"));
        CHECK_FALSE(stack.empty());
        CHECK(stack.top() == "World!");
        CHECK_NOTHROW(stack.pop());
        CHECK_FALSE(stack.empty());
    }
}


TEST_CASE("Widget V1")
{
    std::ostringstream os{};
    constexpr WidgetV1 w{42};
    os << w;
    CHECK(os.str() == "42 V1");
}

TEST_CASE("Widget V2")
{
    std::ostringstream os{};
    constexpr WidgetV2 w{42};
    os << w;
    CHECK(os.str() == "42 V2");
}
