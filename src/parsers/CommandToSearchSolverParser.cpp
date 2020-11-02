#include "CommandToSearchSolverParser.hpp"
#include "SearcherFactory.hpp"
#include "SearchSolver.hpp"
#include "StatusException.hpp"

#include <vector>

namespace parser {

    std::unique_ptr<solver::Solver<searcher::Graph, searcher::SearchResult>> CommandToSearchSolverParser::parse(
        const std::string &command) const {
            // parsing the input command into parts
            std::vector<std::string> commandParts;
            std::string part = "";
            for (const auto x : command)
            {
                if (x == ' ')
                {
                    if (part.size() > 0)
                    {
                        commandParts.push_back(part);
                    }
                    part = "";
                }
                else
                {
                    part += x;
                    if (x == command.at(command.size() - 1))
                    {
                        commandParts.push_back(part);
                    }
                }
            }

            // checking if the command length is legal
            if (commandParts.size() != 3 && commandParts.size() != 2)
            {
                throw status_exception::StatusException("Invalid message length", 3);
            }

            // getting the right searcher, according to the command
            // and throwing exceptions in case that the command is invalid
            searcher::SearcherFactory<std::pair<uint32_t, uint32_t>> searcherFactory;
            if (commandParts[0] == "solve" && commandParts[1] == "find-graph-path")
            {
                std::unique_ptr<searcher::Searcher<searcher::SearchResult, std::pair<uint32_t, uint32_t>>> searcher;
                if (commandParts.size() == 2)
                {
                    searcher = searcherFactory.getDefaultSearcher();
                }
                else
                {
                    searcher = searcherFactory.getSearcher(commandParts[2]);
                }

                if (searcher == nullptr) {
                    throw status_exception::StatusException("Invalid algorithm name", 3);
                }
                
                return std::make_unique<solver::SearchSolver>(std::move(searcher));
            }

            throw status_exception::StatusException("Invalid problem type", 3);
    }
}