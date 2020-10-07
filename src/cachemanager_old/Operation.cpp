#include "Operation.hpp"

namespace operation
{

    Operation::Operation(const uint32_t hashCode) : m_hashCode(hashCode) {}

    uint32_t Operation::getHashCode() const
    {
        return m_hashCode;
    }
}