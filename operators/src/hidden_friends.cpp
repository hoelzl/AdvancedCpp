#include "hidden_friends.hpp"

namespace ops {

[[nodiscard]] bool operator==(
    CompareMeHiddenFriends const& lhs, CompareMeHiddenFriends const& rhs) noexcept
{
    return lhs.id % 100 == rhs.id % 100;
}

[[nodiscard]] bool operator!=(
    CompareMeHiddenFriends const& lhs, CompareMeHiddenFriends const& rhs) noexcept
{
    return !(lhs == rhs);
}

[[nodiscard]] bool
operator<(CompareMeHiddenFriends const& lhs, CompareMeHiddenFriends const& rhs) noexcept
{
    return lhs.id % 100 < rhs.id % 100;
}

[[nodiscard]] bool operator<=(
    CompareMeHiddenFriends const& lhs, CompareMeHiddenFriends const& rhs) noexcept
{
    return !(rhs < lhs);
}

[[nodiscard]] bool
operator>(CompareMeHiddenFriends const& lhs, CompareMeHiddenFriends const& rhs) noexcept
{
    return rhs < lhs;
}

[[nodiscard]] bool operator>=(
    CompareMeHiddenFriends const& lhs, CompareMeHiddenFriends const& rhs) noexcept
{
    return !(lhs < rhs);
}

} // namespace ops
