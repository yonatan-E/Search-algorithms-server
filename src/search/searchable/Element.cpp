#include "Element.hpp"

#include <cstdint>
#include <utility>
#include <cmath>

namespace searcher
{

    typedef std::pair<uint32_t, uint32_t> pair;

    // concrete implementation for calculateHeuristics, in case that the identifier is pair
    template <>
    void Element<pair>::calculateHeuristics(const Element<pair> &startPos, const Element<pair> &endPos)
    {
        m_gScore = abs(getIdentifier().first - startPos.getIdentifier().first) + abs(getIdentifier().second - startPos.getIdentifier().second);
        m_hScore = abs(getIdentifier().first - endPos.getIdentifier().first) + abs(getIdentifier().second - endPos.getIdentifier().second);
    }
}