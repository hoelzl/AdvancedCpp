#include <algorithm>

#include "repeated_vector_wrapper.hpp"
#include "stl.hpp"

int main()
{
    stl::print_stl_info();

    std::vector<int> my_ints{1, 2, 3, 4};

    stl::RepeatedVectorWrapper<int> wrapper{my_ints, 1};

    std::vector<int> result{};
    std::for_each(
        wrapper.begin(), wrapper.end(), [](auto i) { std::printf("%d, ", i); });
}
