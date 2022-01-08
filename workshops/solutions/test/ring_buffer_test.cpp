#include "ring_buffer.hpp"
#include "catch2/catch_test_macros.hpp"

using ring_buffer::RingBuffer;

TEST_CASE("RingBuffer()")
{
    RingBuffer buffer{2};
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
