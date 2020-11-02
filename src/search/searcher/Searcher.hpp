#pragma once

#include "Searchable.hpp"

namespace searcher
{

    /**
     * @brief This class represents a searcher object, that can search on a searchable object
     * 
     * @tparam SearchResult the type of the search result
     * @tparam Identifier the identifier of an element in the searchable object, where the search is doing on
     */
    template <typename SearchResult, typename Identifier>
    class Searcher
    {

    public:
        /**
             * @brief Search on the given searchable object and return the search result
             * 
             * @param searchable the given searchable object, where the search is doing on
             * @return SearchResultType the result of the search
             */
        virtual SearchResult search(const Searchable<Identifier> &searchable) const = 0;

        /**
             * @brief Get the Number Of Evaluated Elements in the search
             * 
             * @return uint32_t the number of the evaluated elements
             */
        virtual uint32_t getNumberOfEvaluatedElements() const = 0;

        /**
             * @brief Virtual destructor
             * 
             */
        virtual ~Searcher() = default;
    };
}