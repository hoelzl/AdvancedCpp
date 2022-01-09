#include "repeated_vector_wrapper.hpp"
#include <catch2/catch_test_macros.hpp>

using stl::RepeatedVectorWrapper;

TEST_CASE("RVW returns end iterator when number of iterations is 0.")
{
    std::vector<int> my_ints{1, 2, 3, 4};

    RepeatedVectorWrapper<int> wrapper{my_ints, 0};

    auto beg{wrapper.begin()};
    auto end{wrapper.end()};

    CHECK(beg == end);
}

TEST_CASE("RVW does not iterate when number of iterations is 0.")
{
    std::vector<int> my_ints{1, 2, 3, 4};

    RepeatedVectorWrapper<int> wrapper{my_ints, 0};

    std::vector<int> result{};
    std::copy(wrapper.begin(), wrapper.end(), std::back_inserter(result));

    CHECK(result.empty());
}


TEST_CASE("RVW iterates once when number of iterations is 1.")
{
    std::vector<int> my_ints{1, 2, 3, 4};

    RepeatedVectorWrapper<int> wrapper{my_ints, 1};

    std::vector<int> result{};
    std::copy(wrapper.begin(), wrapper.end(), std::back_inserter(result));

    CHECK(result == my_ints);
}

TEST_CASE("RVW iterates twice when number of iterations is 2.")
{
    std::vector<int> my_ints{1, 2, 3, 4};

    RepeatedVectorWrapper<int> wrapper{my_ints, 2};

    std::vector<int> result{};
    std::vector<int> expected{1, 2, 3, 4, 1, 2, 3, 4};
    std::copy(wrapper.begin(), wrapper.end(), std::back_inserter(result));

    CHECK(result == expected);
}

TEST_CASE("RVW works when vector is empty.")
{
    std::vector<int> my_ints{};

    RepeatedVectorWrapper<int> wrapper{my_ints, 2};

    std::vector<int> result{};
    std::vector<int> expected{};
    std::copy(wrapper.begin(), wrapper.end(), std::back_inserter(result));

    CHECK(result == expected);
}
