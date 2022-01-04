#include "operators.hpp"

namespace ops {

bool operator==(CompareMe const& lhs, CompareMe const& rhs) noexcept
{
    return lhs.id % 100 == rhs.id % 100;
}

bool operator!=(CompareMe const& lhs, CompareMe const& rhs) noexcept { return !(lhs == rhs); }

bool operator<(CompareMe const& lhs, CompareMe const& rhs) noexcept
{
    return lhs.id % 100 < rhs.id % 100;
}

bool operator<=(CompareMe const& lhs, CompareMe const& rhs) noexcept { return !(rhs < lhs); }

bool operator>(CompareMe const& lhs, CompareMe const& rhs) noexcept { return rhs < lhs; }

bool operator>=(CompareMe const& lhs, CompareMe const& rhs) noexcept { return !(lhs < rhs); }

bool CompareMeMember::operator==(CompareMeMember const& rhs) const noexcept
{
    return id % 100 == rhs.id % 100;
}

bool CompareMeMember::operator!=(CompareMeMember const& rhs) const noexcept
{
    return !(*this == rhs);
}

bool CompareMeMember::operator<(CompareMeMember const& rhs) const noexcept
{
    return id % 100 < rhs.id % 100;
}

bool CompareMeMember::operator<=(CompareMeMember const& rhs) const noexcept
{
    return !(rhs < *this);
}

bool CompareMeMember::operator>(CompareMeMember const& rhs) const noexcept
{
    return rhs < *this;
}

bool CompareMeMember::operator>=(CompareMeMember const& rhs) const noexcept
{
    return !(*this < rhs);
}


} // namespace ops
