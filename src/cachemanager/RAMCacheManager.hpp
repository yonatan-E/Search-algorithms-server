#pragma once

#include "CacheManager.hpp"
#include <unordered_map>
#include <vector>
#include <cstdint>
#include <algorithm>

namespace cache {

    template <typename Problem, typename Solution>
    class RAMCacheManager {
        
        typedef std::pair<Problem, solver::Solver<Problem, Solution>> SolverProblem;

        std::vector<std::pair<SolverProblem, std::weak_ptr<Solution>>> m_cache;
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
                m_cache.erase(m_cache.begin());
            }

            // adding the hash code of the new operation to the vector
            m_cache.push_back({solverProblem, std::make_shared<Solution>(solverProblem.second.solve(solverProblem.first))});

            // if the cache contains the hash code of the operation, moving the hash code of the operation
            // to the end of the vector, according to the LRU algorithm.
            // by moving the hash code of the operation to the end of the vector, we are making
            // the operation more "relevant", because it makes the operation to stay more time in the cache.
        }
        else
        {
            // removing the hash code of the operation from the vector
            auto it = std::find_if(m_cache.begin(), m_cache.end(), [](const std::pair<SolverProblem, std::weak_ptr<Solution>>& p) {
                return p.first == solverProblem;
            });
            m_cache.erase(it);
            // pushing the hash code of the operation to the end of the vector
            m_cache.push_back(*it);
        }

        return getSolution(solverProblem);
    }

    template<typename Problem, typename Solution>
    bool RAMCacheManager<Problem, Solution>::contains(const SolverProblem& solverProblem) const {
        return std::find_if(m_cache.begin(), m_cache.end(), [](const std::pair<SolverProblem, std::weak_ptr<Solution>>& p) {
            return p.first == solverProblem;
        }) != m_cache.end();
    }

    template<typename Problem, typename Solution>
    std::shared_ptr<Solution> RAMCacheManager<Problem, Solution>::getSolution(const SolverProblem& solverProblem) const {
        auto it = std::find_if(m_cache.begin(), m_cache.end(), [](const std::pair<SolverProblem, std::weak_ptr<Solution>>& p) {
            return p.first == solverProblem;
        });
        if (it == m_cache.end()) {
            return nullptr;
        }
        auto solution = it->second.lock();
        if (!solution) {
            it->second = std::make_shared<Solution>(solverProblem.second.solve(solverProblem.first));
        }
        return solution;
    }
}