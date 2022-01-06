#include "operators.hpp"

namespace ops {

bool operator==(const CompareMe& lhs, const CompareMe& rhs) noexcept
{
    return lhs.id % 100 == rhs.id % 100;
}

bool operator!=(const CompareMe& lhs, const CompareMe& rhs) noexcept { return !(lhs == rhs); }

bool operator<(const CompareMe& lhs, const CompareMe& rhs) noexcept
{
    return lhs.id % 100 < rhs.id % 100;
}

bool operator<=(const CompareMe& lhs, const CompareMe& rhs) noexcept { return !(rhs < lhs); }

bool operator>(const CompareMe& lhs, const CompareMe& rhs) noexcept { return rhs < lhs; }

bool operator>=(const CompareMe& lhs, const CompareMe& rhs) noexcept { return !(lhs < rhs); }

bool CompareMeMember::operator==(const CompareMeMember& rhs) const noexcept
{
    return id % 100 == rhs.id % 100;
}

bool CompareMeMember::operator!=(const CompareMeMember& rhs) const noexcept
{
    return !(*this == rhs);
}

bool CompareMeMember::operator<(const CompareMeMember& rhs) const noexcept
{
    return id % 100 < rhs.id % 100;
}

bool CompareMeMember::operator<=(const CompareMeMember& rhs) const noexcept
{
    return !(rhs < *this);
}

bool CompareMeMember::operator>(const CompareMeMember& rhs) const noexcept
{
    return rhs < *this;
}

bool CompareMeMember::operator>=(const CompareMeMember& rhs) const noexcept
{
    return !(*this < rhs);
}


} // namespace ops
