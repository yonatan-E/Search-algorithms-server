#pragma once

#include "Parser.hpp"
#include "Graph.hpp"

namespace parser
{

    /**
     * @brief This class represents an input parser, that parses the given input a graph object.
     * 
     */
    class InputToGraphParser : public Parser<searcher::Graph>
    {

    public:
        /**
             * @brief Parse an input string to a Graph object
             * 
             * @param input the given input string
             * @return searcher::Graph the graph object that the given input string was parsed to
             */
        searcher::Graph parse(const std::string &input) const override;
    };
}