#pragma once

#include <string>

namespace solver
{

    /**
     * @brief This class represents a problem solver.
     * 
     * @tparam Problem the type of the problem
     * @tparam Solution the type of the solution
     */
    template <typename Problem, typename Solution>
    class Solver
    {

    public:
        /**
             * @brief Solve a problem and get its solution
             * 
             * @param problem the object represents the problem
             * @return Solution an object represents the solution of the problem
             */
        virtual Solution solve(const Problem &problem) const = 0;

        /**
         * @brief Virtual destructor
         * 
         */
        virtual ~Solver() = default;
    };
}