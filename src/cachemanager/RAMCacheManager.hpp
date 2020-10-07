#pragma once

#include "CacheManager.hpp"
#include <map>
#include <vector>
#include <cstdint>

namespace cache {

    template <typename Problem, typename Solution>
    class RAMCacheManager {
        
        typedef std::pair<Problem, solver::Solver<Problem, Solution>> SolverProblem;

        std::map<SolverProblem, std::weak_ptr<Solution>> m_cache;
        std::vector<std::weak_ptr<Solution>> m_cacheQueue;
        const uint32_t m_maxSize;

        public:

            RAMCacheManager(uint32_t maxSize);

            std::shared_ptr<Solution> load(const SolverProblem& solverProblem) override;

        protected:

            bool contains(const SolverProblem& solverProblem) const override;

            std::shared_ptr<Solution> getSolution(const SolverProblem& solverProblem) const override;
    };

    template<typename Problem, typename Solution>
    RAMCacheManager<Problem, Solution>::RAMCacheManager(const uint32_t maxSize)
    : m_maxSize(maxSize) {}

    template<typename Problem, typename Solution>
    std::shared_ptr<Solution> RAMCacheManager<Problem, Solution>::load(const SolverProblem& solverProblem)
    {
        // if the cache doesn't contain the hash code of the operation, adding the operation to the cache
        if (!contains(solverProblem))
        {

            // if the cache is full, removing an operation from the cache to make a place for the new operation.
            // we will allways remove the operation which its hash code is the first in the vector.
            if (m_cache.size() >= m_maxSize)
            {
                // removing the hash code of the operation from the vector
                auto removed = m_cacheQueue.begin();
                m_cacheQueue.erase(removed);
                auto it = m_cache.find(*removed);
                m_cache.erase(it);
            }

            // adding the hash code of the new operation to the vector
            m_cache.push_back(operation.getHashCode());

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

    template<typename Problem, typename Solution>
    bool RAMCacheManager<Problem, Solution>::contains(const SolverProblem& solverProblem) const {
        return m_cache.find(solverProblem) != m_cache.end();
    }

    template<typename Problem, typename Solution>
    std::shared_ptr<Solution> RAMCacheManager<Problem, Solution>::getSolution(const SolverProblem& solverProblem) const {
        auto solution = m_cache[solverProblem].lock();
        if (!solverProblem) {
            m_cache[solverProblem] = std::make_shared<Solution>(solverProblem.second.solve(solverProblem.first)); 
        }
        return solution;
    }
}