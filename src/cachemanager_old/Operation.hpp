#pragma once

#include <string>
#include <cstdint>

namespace operation
{

    /**
     * @brief This class represents an operation that can be saved on the cache manager.
     * 
     */
    class Operation
    {

        // the hash code of the operation
        const uint32_t m_hashCode;

    public:
        /**
             * @brief Construct a new Operation object with the given hashCode
             * 
             * @param hashCode the hashCode of the operation
             */
        Operation(const uint32_t hashCode);

        /**
             * @brief Destroy the Operation object
             * 
             */
        virtual ~Operation() = default;

        /**
             * @brief Write the operation result into a file
             *
             * @param filePath the path to the file
             */
        virtual void writeOperationToFile(const std::string &filePath) const = 0;

        /**
             * @brief Get the hashCode of the operation
             * 
             * @return uint32_t the hashCode of the operation
             */
        virtual uint32_t getHashCode() const final;
    };
}