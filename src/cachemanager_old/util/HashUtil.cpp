#include "HashUtil.hpp"
#include "Crc32.h"

namespace util
{

    uint32_t HashUtil::calculateHash(const std::string &string)
    {
        return calculate_crc32c(0, reinterpret_cast<const unsigned char *>(string.c_str()), string.size());
    }
}