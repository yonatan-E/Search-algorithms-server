#pragma once

#include "Operation.hpp"

namespace operation
{

    /**
     * @brief This class represents an operation of solver, that solves a problem.
     * 
     */
    class SolverOperation : public Operation
    {

    public:
        /**
             * @brief Construct a new Solver Operation object
             * 
             * @param hashCode the hashCode of the operation
             * @param result the result of the operation, as a string
             */
        SolverOperation(const uint32_t hashCode, const std::string &result);

        /**
             * @brief Write the operation result into a file
             *
             * @param filePath the path to the file
             */
        void writeOperationToFile(const std::string &filePath) const override;

    private:
        // a strin that represents the result of the operation
        const std::string m_result;
    };
}