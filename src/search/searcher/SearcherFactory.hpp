#pragma once

#include "DFSSearcher.hpp"
#include "BFSSearcher.hpp"
#include "BestFSSearcher.hpp"
#include "AStarSearcher.hpp"

#include <unordered_map>
#include <functional>
#include <memory>

namespace searcher {

    template <typename Identifier>
    class SearcherFactory {

        std::unordered_map<std::string, std::function<std::unique_ptr<Searcher<SearchResult, Identifier>>()>> m_map;

        public:

            SearcherFactory();

            std::unique_ptr<Searcher<SearchResult, Identifier>> getSearcher(const std::string& type) const;

            std::unique_ptr<Searcher<SearchResult, Identifier>> getDefaultSearcher() const;
    };

    template <typename Identifier>
    SearcherFactory<Identifier>::SearcherFactory() {
        m_map.emplace("DFS", [](){return std::make_unique<DFSSearcher<Identifier>>();});
        m_map.emplace("BFS", [](){return std::make_unique<BFSSearcher<Identifier>>();});
        m_map.emplace("BestFS", [](){return std::make_unique<BestFSSearcher<Identifier>>();});
        m_map.emplace("A*", [](){return std::make_unique<AStarSearcher<Identifier>>();});
    }

    template <typename Identifier>
    std::unique_ptr<Searcher<SearchResult, Identifier>> SearcherFactory<Identifier>::getSearcher(const std::string& type) const {
        if (m_map.find(type) == m_map.end()) {
            return nullptr;
        }
        return m_map.at(type)();
    }

    template <typename Identifier>
    std::unique_ptr<Searcher<SearchResult, Identifier>> SearcherFactory<Identifier>::getDefaultSearcher() const {
        return m_map.at("BestFS")();
    }
}