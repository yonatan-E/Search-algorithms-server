#pragma once

#include "Parser.hpp"
#include "Solver.hpp"
#include "Graph.hpp"
#include "SearchResult.hpp"

#include <memory>

namespace parser {

    /**
     * @brief This class represents a command parser, that parses the given command to a solver object.
     * 
     */
    class CommandToSearchSolverParser : public Parser<std::unique_ptr<solver::Solver<searcher::Graph, searcher::SearchResult>>> {
        
        public:
            /**
             * @brief Parse an input command string to a Solver object
             * 
             * @param command the input command string
             * @return std::unique_ptr<solver::Solver<searcher::Graph, searcher::SearchResult>>
             *      the object that the given input command will be parsed to
             */
            virtual std::unique_ptr<solver::Solver<searcher::Graph, searcher::SearchResult>> parse(
                const std::string &command) const override;
    };
}