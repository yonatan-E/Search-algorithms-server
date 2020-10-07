#pragma once

#include "Operation.hpp"
#include <vector>

namespace cache
{

    /**
     * @brief This class represents a cache manager
     * 
     */
    class CacheManager
    {

        // a vector with the hashCodes of all of the operations in the cache
        std::vector<uint32_t> m_hashCodes;
        // the maximum size of the cache
        const uint32_t m_maxSize;
        // the path to the directory where the cache files will be saved
        const std::string m_directoryPath;

    public:
        /**
             * @brief Construct a new Cache Manager object
             * 
             * @param maxSize the maximum size of the cache
             * @param directoryPath the path to the directory where the cache files will be saved
             */
        CacheManager(const uint32_t maxSize, std::string directoryPath);

        /**
             * @brief Load the operation into the cache:
                    If the operation doesn't exist on the cache, add it to the cache.
                    If the operation exists on the cache, make it more relevant on the cache.
             * 
             * @param operation the operation to load into the cache
             */
        void load(const operation::Operation &operation);

        /**
             * @brief Check if the given hashCode exists in the cache
             * 
             * @param hashCode the given hashCode
             * @return true if the given hashCode exists in the cache
             * @return false if the given hashCode doesn't exist in the cache
             */
        bool contains(const uint32_t hashCode) const;

        /**
             * @brief Get the content of the operation file in the cache
             * 
             * @param hashCode the hashCode of the operation
             * @return std::string the content of the operation file in the cache
             */
        std::string getOperationFileContent(const uint32_t hashCode) const;

    private:
        /**
             * @brief Get the path of the operation file of the operation with the given hashCode
             * 
             * @param hashCode the given hashCode
             * @return std::string the path to the operation file of the operation with the given hashCode
             */
        std::string getOperationFilePath(const uint32_t hashCode) const;
    };
}