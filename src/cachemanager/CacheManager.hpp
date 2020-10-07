#pragma once

#include "Solver.hpp"
#include <memory>

namespace cache {

    template <typename Problem, typename Solution>
    class CacheManager {

        public:

            virtual std::shared_ptr<Solution> load(const Problem& problem, const solver::Solver& solver) = 0;

        protected:

            virtual bool contains(const Problem& problem) const = 0;

            virtual std::shared_ptr<Solution> getSolution(const Problem& problem, const solver::Solver& solver) const = 0;
    };
}