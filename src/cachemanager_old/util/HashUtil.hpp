#pragma once

#include <string>
#include <cstdint>

namespace util
{

    /**
     * @brief This class is in charge of calculating hash of strings.
     * 
     */
    class HashUtil
    {

    public:
        /**
             * @brief Calculate the hash of a string
             * 
             * @param string the given string
             * @return uint32_t the hash of the string
             */
        static uint32_t calculateHash(const std::string &string);
    };
}