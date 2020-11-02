#include "SearchSolver.hpp"
#include "StatusException.hpp"

namespace solver
{

    SearchSolver::SearchSolver(std::unique_ptr<searcher::Searcher<searcher::SearchResult, std::pair<uint32_t, uint32_t>>> searcher)
        : m_searcher(std::move(searcher)) {}

    searcher::SearchResult SearchSolver::solve(const searcher::Graph &problem) const
    {

        try
        {
            return m_searcher->search(problem);
        }
        catch (const searcher::exceptions::PathDoesNotExistException &e)
        {
            throw status_exception::StatusException(e.what(), 1);
        }
        catch (const searcher::exceptions::InvalidPositionException &e)
        {
            throw status_exception::StatusException(e.what(), 2);
        }
    }
}