#include "SolverOperation.hpp"
#include "OperationExceptions.hpp"

#include <fstream>

namespace operation
{

    SolverOperation::SolverOperation(const uint32_t hashCode, const std::string &result)
        : Operation(hashCode),
          m_result(result) {}

    void SolverOperation::writeOperationToFile(const std::string &filePath) const
    {
        // opening the file using ofstream
        std::ofstream file(filePath, std::ios::trunc);

        // checking if an error has occured while opening the file
        if (!file.is_open())
        {
            throw exceptions::FileOpenException();
        }

        // writing the result string into the file
        file << m_result;

        // closing the ofstream
        file.close();
    }
}