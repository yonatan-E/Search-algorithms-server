#pragma once

#include "AbstractSearcher.hpp"

#include <queue>

namespace searcher
{

    /**
     * @brief This class represents an BestFS searcher. Uses a priority queue as a container.
     * 
     * @tparam Identifier the identifier of an element in the searchable object, where the search is doing on
     */
    template <typename Identifier>
    class BestFSSearcher : public AbstractSearcher<Identifier>
    {

        // the proirity queue which will be used for the BestFS algorithm.
        // the best element in the priority queue will be the element which its H Score is the best.
        // so, the elements in the priority queue will be ordered using the element H Score comparator
        mutable std::priority_queue<Element<Identifier>, std::vector<Element<Identifier>>, CompareByHScore<Identifier>> pqueue;

    protected:
        /**
             * @brief Push an element to the container of the search
             * 
             * @param element the given element
             */
        void pushToContainer(const Element<Identifier> &element) const override
        {
            pqueue.push(element);
        }

        /**
             * @brief Pop an element from the container of the search
             * 
             * @return Element<Identifier> the popped element
             */
        Element<Identifier> popFromContainer() const override
        {
            const Element<Identifier> popped = pqueue.top();
            pqueue.pop();
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
            return pqueue.empty();
        }

        /**
             * @brief Clear the container of the search
             * 
             */
        void clearContainer() const override
        {
            while (!pqueue.empty())
            {
                pqueue.pop();
            }
        }

        /**
             * @brief Get the name of the search algorithm
             * 
             * @return std::string the algorithm name
             */
        std::string getAlgorithmName() const override
        {
            return "BestFS";
        }
    };
}