#include "ring_buffer.hpp"
#include "catch2/catch_test_macros.hpp"
#include <string>

using namespace std::string_literals;

TEST_CASE("RingBuffer()")
{
    ring_buffer::RingBuffer buffer{2};
    constexpr auto a_random_number{42};

    SECTION("A new buffer is empty.") {
        CHECK(buffer.empty());    
    }

    SECTION("Buffer is not empty after put().") {
        buffer.put(a_random_number);
        CHECK_FALSE(buffer.empty());
    }

    SECTION("Pushing and popping a single number works.") {
        buffer.put(1);
        CHECK(buffer.get() == 1);
    }

    SECTION("Pushing and popping three numbers works.") {
        buffer.put(1);
        buffer.put(2);
        buffer.put(3);
        CHECK(buffer.get() == 2);
        CHECK(buffer.get() == 3);
    }

    SECTION("Mixing put() and get() works.") {
        buffer.put(1);
        buffer.put(2);
        REQUIRE(buffer.get() == 1);
        buffer.put(3);
        buffer.put(4);

        CHECK(buffer.get() == 3);
    }
}

TEST_CASE("generic RingBuffer() for ints")
{
    generic_ring_buffer::RingBuffer<int> buffer{2};
    constexpr auto a_random_number{42};

    SECTION("A new buffer is empty.") {
        CHECK(buffer.empty());    
    }

    SECTION("Buffer is not empty after put().") {
        buffer.put(a_random_number);
        CHECK_FALSE(buffer.empty());
    }

    SECTION("Pushing and popping a single number works.") {
        buffer.put(1);
        CHECK(buffer.get() == 1);
    }

    SECTION("Pushing and popping three numbers works.") {
        buffer.put(1);
        buffer.put(2);
        buffer.put(3);
        CHECK(buffer.get() == 2);
        CHECK(buffer.get() == 3);
    }

    SECTION("Mixing put() and get() works.") {
        buffer.put(1);
        buffer.put(2);
        REQUIRE(buffer.get() == 1);
        buffer.put(3);
        buffer.put(4);

        CHECK(buffer.get() == 3);
    }
}

TEST_CASE("generic RingBuffer() for strings")
{
    generic_ring_buffer::RingBuffer<std::string> buffer{2};
    const auto a_random_string{"abc"s};

    SECTION("A new buffer is empty.") {
        CHECK(buffer.empty());    
    }

    SECTION("Buffer is not empty after put().") {
        buffer.put(a_random_string);
        CHECK_FALSE(buffer.empty());
    }

    SECTION("Pushing and popping a single number works.") {
        buffer.put("a"s);
        CHECK(buffer.get() == "a"s);
    }

    SECTION("Pushing and popping three numbers works.") {
        buffer.put("a"s);
        buffer.put("x"s);
        buffer.put("y"s);
        CHECK(buffer.get() == "x"s);
        CHECK(buffer.get() == "y"s);
    }

    SECTION("Mixing put() and get() works.") {
        buffer.put("a"s);
        buffer.put("x"s);
        REQUIRE(buffer.get() == "a"s);
        buffer.put("y"s);
        buffer.put("z"s);

        CHECK(buffer.get() == "y"s);
    }
}
