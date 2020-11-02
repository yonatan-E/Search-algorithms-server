#pragma once

#include "Element.hpp"

#include <vector>
#include <string>

namespace searcher
{

    /**
     * @brief This class represents a searchable object
     * 
     * @tparam Identifier the identifier of an element in the searchable object
     */
    template <typename Identifier>
    class Searchable {

        public:

            /**
             * @brief Get the Start Element of the search
             * 
             * @return const Element<Identifier>& the element where the search starts
             */
            virtual const Element<Identifier>& getStartElement() const = 0;

            /**
             * @brief Get the End Element of the search
             * 
             * @return const Element<Identifier>& the element where the search end
             */
            virtual const Element<Identifier>& getEndElement() const = 0;

            /**
             * @brief Get the All Reachable Elements object of an element
             * 
             * @param current the given element
             * @return std::vector<Element<Identifier>> vector with all of the reachable elements of the given element 
             */
            virtual std::vector<Element<Identifier>> getAllReachableElements(const Element<Identifier>& current) const = 0;

            /**
             * @brief Get the Direction between two elements in the searchable object, represented by a string
             * 
             * @param origin the origin element
             * @param destination the destination element
             * @return std::string a string that represents the direction from origin to destination
             */
            virtual std::string getDirection(const Element<Identifier>& origin, const Element<Identifier>& destination) const = 0;

            /**
             * @brief Virtual destructor
             * 
             */
            virtual ~Searchable() = default;
    };
}