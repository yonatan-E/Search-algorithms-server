#pragma once

#include "AbstractSearchable.hpp"
#include "Matrix.hpp"
#include "Element.hpp"

#include <cstdint>
#include <utility>

namespace searcher
{

    typedef std::pair<uint32_t, uint32_t> pair;
    typedef Element<pair> graphElement;

    /**
     * @brief This class represents a graph, which is defined by a matrix
     * 
     */
    class Graph : public AbstractSearchable<pair>
    {

        // the matrix which defines the structure of the graph
        const matrix::Matrix m_graphMatrix;

    public:
        /**
             * @brief Construct a new Graph object
             * 
             * @param graphMatrix the matrix which defines the graph
             * @param startPos 
             * @param endPos 
             */
        Graph(const matrix::Matrix &graphMatrix, const pair &startPos, const pair &endPos);

        /**
             * @brief Get the All Reachable Elements object of an element
             * 
             * @param current the given element
             * @return std::vector<Element<Identifier>> vector with all of the reachable elements of the given element 
             */
        std::vector<graphElement> getAllReachableElements(const graphElement &current) const override;

        /**
             * @brief Get the Direction between two elements in the searchable object, represented by a string
             * 
             * @param origin the origin element
             * @param destination the destination element
             * @return std::string a string that represents the direction from origin to destination.
             *      in this case, can be: left, right, up, down.
             */
        std::string getDirection(const graphElement &origin, const graphElement &destination) const override;

    protected:
        /**
             * @brief Check if an element is a valid element in the searchable
             * 
             * @param element the given element
             * @return true if the given element is a valid element
             * @return false if the given element is not a valid element
             */
        bool isValidElement(const graphElement &element) const override;
    };
}