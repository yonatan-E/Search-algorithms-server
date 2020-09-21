#pragma once

#include "Searchable.hpp"
#include "SearchExceptions.hpp"

namespace searcher {
    
    template <typename Identifier>
    class AbstractSearchable : public Searchable<Identifier> {

        const Element<Identifier> m_startPos;
        const Element<Identifier> m_endPos;

        public:
        
            AbstractSearchable(const Element<Identifier>& startPos, const Element<Identifier>& endPos)
            : m_startPos(startPos), m_endPos(endPos) {
                // checking if the start position is valid
                if (!isValidElement(startPos)) {
                    throw exceptions::InvalidStartPositionException();
                }

                // checking if the end position is valid
                if (!isValidElement(endPos)) {
                    throw exceptions::InvalidEndPositionException();
                }
            }

            virtual const Element<Identifier>& getStartElement() const final {
                return m_startPos;
            }

            virtual const Element<Identifier>& getEndElement() const final {
                return m_endPos;
            }

            virtual std::vector<Element<Identifier>> getAllReachableElements(const Element<Identifier>& current) const = 0;

            virtual std::string getDirection(const Element<Identifier>& origin, const Element<Identifier>& destination) const = 0;

            virtual bool isValidElement(const Element<Identifier>& element) const = 0;

            virtual ~AbstractSearchable() = default;
    };
}