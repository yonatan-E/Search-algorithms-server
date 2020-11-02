#pragma once

#include "Searcher.hpp"
#include "SearchResult.hpp"
#include "SearchExceptions.hpp"

#include <set>
#include <map>

namespace searcher
{

    /**
     * @brief This class is a base class for some searcher object classes.
     *      This class assumes that all of the searchers that inherit from it use a specific container for the search.
     * 
     * @tparam Identifier the identifier of an element in the searchable object, where the search is doing on
     */
    template <typename Identifier>
    class AbstractSearcher : public Searcher<SearchResult, Identifier>
    {

        // the number of the evaluated elements
        mutable uint32_t m_evaluatedElements;

    public:
        /**
             * @brief Search on the given searchable object and return the search result
             * 
             * @param searchable the given searchable object, where the search is doing on
             * @return SearchResultType the result of the search
             */
        virtual SearchResult search(const Searchable<Identifier> &searchable) const override
        {
            // clearing the container, to make sure it is empty
            clearContainer();
            // reseting the number of evaluated elements
            m_evaluatedElements = 0;

            // set of the visited elements
            std::set<Element<Identifier>, CompareByIdentifier<Identifier>> visited;

            // this map will hold for every element in the path, its previous element in the path.
            // the elements will be ordered in the map using the element Identifier comparator
            std::map<Element<Identifier>, Element<Identifier>, CompareByIdentifier<Identifier>> cameFrom;

            // marking the start element as visited
            visited.insert(searchable.getStartElement());
            // adding the start element to the container
            pushToContainer(searchable.getStartElement());

            while (!isContainerEmpty())
            {
                // popping an element from the container
                const auto current = popFromContainer();

                // in case that the popped element is the end element, then finishing the search
                if (current == searchable.getEndElement())
                {
                    break;
                }

                // else, evaluating the current element
                ++m_evaluatedElements;
                // getting all of the reachable elements of the popped element
                for (auto &reachable : searchable.getAllReachableElements(current))
                {
                    // if the reachable element has not been visited, then marking it as visited,
                    // adding it to the container, and getting its previos element in the path
                    if (visited.find(reachable) == visited.end())
                    {
                        visited.insert(reachable);
                        pushToContainer(reachable);
                        cameFrom.emplace(reachable, current);
                    }
                }
            }

            // if the end element has not been visited, then the path does not exist
            if (visited.find(searchable.getEndElement()) == visited.end())
            {
                throw exceptions::PathDoesNotExistException();
            }

            return this->reconstructPath(searchable, cameFrom);
        }

        /**
             * @brief Get the Number Of Evaluated Elements in the search
             * 
             * @return uint32_t the number of the evaluated elements
             */
        uint32_t getNumberOfEvaluatedElements() const override
        {
            return m_evaluatedElements;
        }

    protected:
        /**
             * @brief Reconstruct the path of the search
             * 
             * @param searchable the searchable object, where the search is doing on 
             * @param cameFrom a map that saves for every element in the result path, its previous element in the path
             * @return SearchResult the search result, which was created from the given data
             */
        virtual SearchResult reconstructPath(
            const Searchable<Identifier> &searchable,
            std::map<Element<Identifier>, Element<Identifier>, CompareByIdentifier<Identifier>> &cameFrom) const
        {

            // this vector will hold the directions of the path from the start element to the end element
            std::vector<std::string> directions;

            // this variable will hold the total cost of the path.
            // first, initializing it just with the cost of the start element
            auto pathCost = 0;
            if (searchable.getStartElement().getIdentifier() != searchable.getEndElement().getIdentifier())
            {
                pathCost += searchable.getStartElement().getValue();
            }

            // iterating over the elements, and initializing the directions vector according to the path
            const auto *temp = &searchable.getEndElement();
            while (*temp != searchable.getStartElement())
            {
                // adding the cost of the current element to the total cost of the path
                pathCost += temp->getValue();
                // adding a direction between two elements in the path
                directions.insert(directions.begin(), searchable.getDirection(cameFrom.at(*temp), *temp));
                // moving to the previous element
                temp = &cameFrom.at(*temp);
            }

            return SearchResult(directions, pathCost, getAlgorithmName());
        }

        /**
             * @brief Push an element to the container of the search
             * 
             * @param element the given element
             */
        virtual void pushToContainer(const Element<Identifier> &element) const = 0;

        /**
             * @brief Pop an element from the container of the search
             * 
             * @return Element<Identifier> the popped element
             */
        virtual Element<Identifier> popFromContainer() const = 0;

        /**
             * @brief Check if the container of the search is empty
             * 
             * @return true if the container is empty
             * @return false if the container is not empty
             */
        virtual bool isContainerEmpty() const = 0;

        /**
             * @brief Clear the container of the search
             * 
             */
        virtual void clearContainer() const = 0;

        /**
             * @brief Get the name of the search algorithm
             * 
             * @return std::string the algorithm name
             */
        virtual std::string getAlgorithmName() const = 0;

        /**
             * @brief Virtual destructor
             * 
             */
        virtual ~AbstractSearcher() = default;
    };
}