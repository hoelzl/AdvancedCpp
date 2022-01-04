#include "hidden_friends.hpp"

namespace ops {

bool operator==(CompareMeHiddenFriends const& lhs, CompareMeHiddenFriends const& rhs)
{
    return lhs.id % 100 == rhs.id % 100;
}

bool operator!=(CompareMeHiddenFriends const& lhs, CompareMeHiddenFriends const& rhs)
{
    return !(lhs == rhs);
}

bool operator<(CompareMeHiddenFriends const& lhs, CompareMeHiddenFriends const& rhs)
{
    return lhs.id % 100 < rhs.id % 100;
}

bool operator<=(CompareMeHiddenFriends const& lhs, CompareMeHiddenFriends const& rhs)
{
    return !(rhs < lhs);
}

bool operator>(CompareMeHiddenFriends const& lhs, CompareMeHiddenFriends const& rhs)
{
    return rhs < lhs;
}

bool operator>=(CompareMeHiddenFriends const& lhs, CompareMeHiddenFriends const& rhs)
{
    return !(lhs < rhs);
}

} // namespace ops
