#include "operators.hpp"

namespace ops {

bool operator==(CompareMe const& lhs, CompareMe const& rhs)
{
    return lhs.id % 100 == rhs.id % 100;
}

bool operator!=(CompareMe const& lhs, CompareMe const& rhs) { return !(lhs == rhs); }

bool operator<(CompareMe const& lhs, CompareMe const& rhs)
{
    return lhs.id % 100 < rhs.id % 100;
}

bool operator<=(CompareMe const& lhs, CompareMe const& rhs) { return !(rhs < lhs); }

bool operator>(CompareMe const& lhs, CompareMe const& rhs) { return rhs < lhs; }

bool operator>=(CompareMe const& lhs, CompareMe const& rhs) { return !(lhs < rhs); }

bool CompareMeMember::operator==(CompareMeMember const& rhs) const
{
    return id % 100 == rhs.id % 100;
}

bool CompareMeMember::operator!=(CompareMeMember const& rhs) const
{
    return !(*this == rhs);
}

bool CompareMeMember::operator<(CompareMeMember const& rhs) const
{
    return id % 100 < rhs.id % 100;
}

bool CompareMeMember::operator<=(CompareMeMember const& rhs) const
{
    return !(rhs < *this);
}

bool CompareMeMember::operator>(CompareMeMember const& rhs) const
{
    return rhs < *this;
}

bool CompareMeMember::operator>=(CompareMeMember const& rhs) const
{
    return !(*this < rhs);
}


} // namespace ops
