#pragma once

#include "AbstractSearcher.hpp"

#include <stack>

namespace searcher
{

    /**
     * @brief This class represents an DFS searcher. Uses a stack as a container.
     * 
     * @tparam Identifier the identifier of an element in the searchable object, where the search is doing on
     */
    template <typename Identifier>
    class DFSSearcher : public AbstractSearcher<Identifier>
    {

        // the stack which will be used for the DFS algorithm
        mutable std::stack<Element<Identifier>> stack;

    protected:
        /**
             * @brief Push an element to the container of the search
             * 
             * @param element the given element
             */
        void pushToContainer(const Element<Identifier> &element) const override
        {
            stack.push(element);
        }

        /**
             * @brief Pop an element from the container of the search
             * 
             * @return Element<Identifier> the popped element
             */
        Element<Identifier> popFromContainer() const override
        {
            const Element<Identifier> popped = stack.top();
            stack.pop();
            return popped;
        }

        /**
             * @brief Check if the container of the search is empty
             * 
             * @return true if the container is empty
             * @return false if the container is not empty
             */
        bool isContainerEmpty() const override
        {
            return stack.empty();
        }

        /**
             * @brief Clear the container of the search
             * 
             */
        void clearContainer() const override
        {
            while (!stack.empty())
            {
                stack.pop();
            }
        }

        /**
             * @brief Get the name of the search algorithm
             * 
             * @return std::string the algorithm name
             */
        std::string getAlgorithmName() const override
        {
            return "DFS";
        }
    };
}
