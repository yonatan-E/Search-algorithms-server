#pragma once

#include "AbstractSearcher.hpp"

#include <queue>

namespace searcher
{

    /**
     * @brief This class represents an BFS searcher. Uses a queue as a container.
     * 
     * @tparam Identifier the identifier of an element in the searchable object, where the search is doing on
     */
    template <typename Identifier>
    class BFSSearcher : public AbstractSearcher<Identifier>
    {

        // the queue which will be used for the BFS algorithm
        mutable std::queue<Element<Identifier>> queue;

    protected:
        /**
             * @brief Push an element to the container of the search
             * 
             * @param element the given element
             */
        void pushToContainer(const Element<Identifier> &element) const override
        {
            queue.push(element);
        }

        /**
             * @brief Pop an element from the container of the search
             * 
             * @return Element<Identifier> the popped element
             */
        Element<Identifier> popFromContainer() const override
        {
            const Element<Identifier> popped = queue.front();
            queue.pop();
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
            return queue.empty();
        }

        /**
             * @brief Clear the container of the search
             * 
             */
        void clearContainer() const override
        {
            while (!queue.empty())
            {
                queue.pop();
            }
        }

        /**
             * @brief Get the name of the search algorithm
             * 
             * @return std::string the algorithm name
             */
        std::string getAlgorithmName() const override
        {
            return "BFS";
        }
    };
}