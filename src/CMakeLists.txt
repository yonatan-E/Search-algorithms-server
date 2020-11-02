cmake_minimum_required(VERSION 3.0.0)
project(Project VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic -Werror -Wshadow)
enable_testing()

find_package (Threads REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(HEADER_FILES cachemanager/CacheManager.hpp cachemanager/Operation.hpp cachemanager/SolverOperation.hpp
cachemanager/util/HashUtil.hpp cachemanager/util/Crc32.h exceptions/OperationExceptions.hpp
exceptions/SearchExceptions.hpp exceptions/ServerExceptions.hpp exceptions/StatusException.hpp
parsers/Parser.hpp parsers/InputToGraphParser.hpp parsers/CommandToSearchSolverParser.hpp search/searchable/Searchable.hpp 
search/searchable/AbstractSearchable.hpp search/searchable/Graph.hpp search/searchable/Element.hpp 
search/searchable/matrix/Matrix.hpp search/searchable/matrix/ErrorCode.hpp search/searchable/matrix/Matrix.h 
search/searchable/matrix/ErrorCode.h search/searcher/Searcher.hpp search/searcher/AbstractSearcher.hpp
search/searcher/SearchResult.hpp search/searcher/DFSSearcher.hpp search/searcher/BFSSearcher.hpp 
search/searcher/BestFSSearcher.hpp search/searcher/AStarSearcher.hpp search/searcher/SearcherFactory.hpp
server/Server.hpp server/SerialServer.hpp server/ParallelServer.hpp server/ServerFactory.hpp
clienthandlers/ClientHandler.hpp clienthandlers/AbstractClientHandler.hpp clienthandlers/SolverClientHandler.hpp
solvers/Solver.hpp solvers/SearchSolver.hpp)

include_directories(${CMAKE_SOURCE_DIR}/cachemanager ${CMAKE_SOURCE_DIR}/cachemanager/util ${CMAKE_SOURCE_DIR}/exceptions
${CMAKE_SOURCE_DIR}/parsers ${CMAKE_SOURCE_DIR}/search/searchable ${CMAKE_SOURCE_DIR}/search/searchable/matrix ${CMAKE_SOURCE_DIR}/search/searcher
${CMAKE_SOURCE_DIR}/server ${CMAKE_SOURCE_DIR}/clienthandlers ${CMAKE_SOURCE_DIR}/solvers)

link_directories(${CMAKE_SOURCE_DIR}/bin)

add_executable(ex4.out main.cpp cachemanager/CacheManager.cpp cachemanager/Operation.cpp cachemanager/SolverOperation.cpp
cachemanager/util/HashUtil.cpp cachemanager/util/Crc32.c exceptions/OperationExceptions.cpp
exceptions/SearchExceptions.cpp exceptions/ServerExceptions.cpp exceptions/StatusException.cpp
parsers/InputToGraphParser.cpp parsers/CommandToSearchSolverParser.cpp
search/searchable/Graph.cpp search/searchable/Element.cpp search/searchable/matrix/Matrix.cpp 
search/searchable/matrix/ErrorCode.cpp
search/searcher/SearchResult.cpp server/SerialServer.cpp server/ParallelServer.cpp server/ServerFactory.cpp
clienthandlers/AbstractClientHandler.cpp solvers/SearchSolver.cpp)

target_include_directories(ex4.out PRIVATE ${CMAKE_SOURCE_DIR}/cachemanager ${CMAKE_SOURCE_DIR}/cachemanager/util ${CMAKE_SOURCE_DIR}/exceptions
${CMAKE_SOURCE_DIR}/parsers ${CMAKE_SOURCE_DIR}/search/searchable ${CMAKE_SOURCE_DIR}/search/searchable/matrix ${CMAKE_SOURCE_DIR}/search/searcher
${CMAKE_SOURCE_DIR}/server ${CMAKE_SOURCE_DIR}/clienthandlers ${CMAKE_SOURCE_DIR}/solvers)
target_link_libraries(ex4.out matrix ${CMAKE_THREAD_LIBS_INIT})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)