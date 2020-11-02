#include "CacheManager.hpp"
#include "OperationExceptions.hpp"

#include <fstream>
#include <algorithm>
#include <iterator>
#include <sys/stat.h>
#include <unistd.h>

using namespace operation;

namespace cache
{

    CacheManager::CacheManager(const uint32_t maxSize, std::string directoryPath)
        : m_maxSize(maxSize), m_directoryPath(std::move(directoryPath))
    {

        // checking if the directory exists
        struct stat buffer;
        if (stat(m_directoryPath.c_str(), &buffer) != 0)
        {
            // if the directory doesn't exist, creating a new one
            // the mode of the directory, always 0777 in our case
            uint32_t mode = 0777;
            if (mkdir(m_directoryPath.c_str(), mode) != 0)
            {
                // throwing an exception in case that the directory creation failed
                throw std::system_error(errno, std::system_category());
            }
        }

        // opening the info file using ifstream
        std::ifstream info(m_directoryPath + "/info.txt");

        // if the file isn't exist, creating the file using ofstream
        if (!info.is_open())
        {
            std::ofstream creator(m_directoryPath + "/info.txt");
            creator.close();
        }

        // reading the content of the info file into the vector
        std::copy(std::istream_iterator<uint32_t>(info), std::istream_iterator<uint32_t>(), std::back_inserter(m_hashCodes));

        // closing the ifstream
        info.close();
    }

    void CacheManager::load(const Operation &operation)
    {
        // if the cache doesn't contain the hash code of the operation, adding the operation to the cache
        if (!contains(operation.getHashCode()))
        {

            // if the cache is full, removing an operation from the cache to make a place for the new operation.
            // we will allways remove the operation which its hash code is the first in the vector.
            if (m_hashCodes.size() >= m_maxSize)
            {

                // removing the file of the operation from the cache directory,
                // and checking if an error has occured while removing the file
                if (remove(getOperationFilePath(*(m_hashCodes.begin())).c_str()) != 0)
                {
                    throw exceptions::FileDeleteException();
                }

                // removing the hash code of the operation from the vector
                m_hashCodes.erase(m_hashCodes.begin());
            }

            // adding the hash code of the new operation to the vector
            m_hashCodes.push_back(operation.getHashCode());

            // if the cache contains the hash code of the operation, moving the hash code of the operation
            // to the end of the vector, according to the LRU algorithm.
            // by moving the hash code of the operation to the end of the vector, we are making
            // the operation more "relevant", because it makes the operation to stay more time in the cache.
        }
        else
        {
            // removing the hash code of the operation from the vector
            m_hashCodes.erase(std::find(m_hashCodes.begin(), m_hashCodes.end(), operation.getHashCode()));
            // pushing the hash code of the operation to the end of the vector
            m_hashCodes.push_back(operation.getHashCode());
        }

        // writing the new vector into the info file
        // opening the info file using ofstream
        std::ofstream info(m_directoryPath + "/info.txt", std::ios::trunc);

        // checking is an error has occured while opening the file
        if (!info.is_open())
        {
            throw exceptions::FileOpenException();
        }

        // writing the vector into the info file
        for (const auto hashCode : m_hashCodes)
        {
            info << hashCode << '\n';
        }

        // finally, adding the file of the new operation to the cache
        operation.writeOperationToFile(getOperationFilePath(operation.getHashCode()));
    }

    bool CacheManager::contains(const uint32_t hashCode) const
    {
        // trying to find the hash code in the vector
        return std::find(m_hashCodes.begin(), m_hashCodes.end(), hashCode) != m_hashCodes.end();
    }

    std::string CacheManager::getOperationFileContent(const uint32_t hashCode) const
    {
        // opening the file
        std::ifstream in(getOperationFilePath(hashCode));

        // checking if an error has occured while opening the file
        if (!in)
        {
            throw exceptions::FileOpenException();
        }

        // reading the content from the file
        auto content = std::string{std::istreambuf_iterator<char>{in}, std::istreambuf_iterator<char>{}};

        // checking if an error has occured while reading from the file
        if (!in)
        {
            throw exceptions::FileReadException();
        }

        return content;
    }

    std::string CacheManager::getOperationFilePath(const uint32_t hashCode) const
    {
        // returning the path to the file of the operation with the given hashCode
        return m_directoryPath + "/" + std::to_string(hashCode) + ".txt";
    }
}