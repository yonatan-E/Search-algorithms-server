#pragma once

#include "AbstractClientHandler.hpp"
#include "Solver.hpp"
#include "Parser.hpp"
#include "CacheManager.hpp"
#include "SolverOperation.hpp"
#include "StatusException.hpp"
#include "HashUtil.hpp"

#include <thread>
#include <unistd.h>
#include <chrono>

namespace server_side {

    namespace client_handler {
        
        /**
         * @brief This class represents a client handler which handle the client using a specific solver.
         * 
         * @tparam Problem the type problem type of the solver
         * @tparam Solution the solution type of the solver
         */
        template <typename Problem, typename Solution>
        class SolverClientHandler : public AbstractClientHandler {

            // the version
            static constexpr double s_VERSION = 1.0;
            // the status for success
            static constexpr uint32_t s_SUCCESS_STATUS = 0;
            // the length of an empty response
            static constexpr const char* s_EMPTY_RESPONSE = "";

            // the solver factory, used to create the concrete solver
            std::unique_ptr<parser::Parser<std::unique_ptr<solver::Solver<Problem, Solution>>>> m_commandParser;
            // the input parser, used to parse the input problem
            std::unique_ptr<parser::Parser<Problem>> m_inputParser;
            // the cache manager used to save previous solutions
            mutable cache::CacheManager m_cacheManager;

            public:

                /**
                 * @brief Construct a new Solver Client Handler object
                 * 
                 * @param cache the given cache manager
                 */
                SolverClientHandler(
                    std::unique_ptr<parser::Parser<std::unique_ptr<solver::Solver<Problem, Solution>>>> commandParser,
                    std::unique_ptr<parser::Parser<Problem>> inputParser,
                    const cache::CacheManager& cacheManager)
                : m_commandParser(std::move(commandParser)),
                m_inputParser(std::move(inputParser)),
                m_cacheManager(cacheManager) {}

                /**
                 * @brief Handle a specific client
                 * 
                 * @param clientSocket the client socket
                 */
                void handleClient(const uint32_t clientSocket) const override {

                    // read problem
                    std::string commandString;

                    bool finished = false;
                    bool timedout = false;

                    try {
                        // waiting for the client message in a different thread
                        std::thread readThread(readSockTrigger, std::ref(*this), clientSocket, std::ref(commandString), std::ref(finished));
                        // counting the timeout
                        timeout(finished, timedout);

                        readThread.join();

                        // if the timeout hasn't been reached, then the client hasn't connected in the last 5 seconds,
                        // so closing the connection
                        if(timedout){
                            try{
                                closeSock(clientSocket);
                            } catch(...) {}
                                return;
                        }
                    } catch (const status_exception::StatusException& e) {
                        
                        // if couldn't read from the socket, then sending error log and closing the connection
                        try {
                            writeSock(clientSocket, getLog(s_VERSION, e.getStatus(), s_EMPTY_RESPONSE));
                        } catch (...) {}

                        try {
                            closeSock(clientSocket);
                        } catch (...) {}
                        
                        return;
                    }

                    // if the client has connected in the last 5 seconds, then sending a success log
                    try {
                        writeSock(clientSocket, getLog(s_VERSION, s_SUCCESS_STATUS, s_EMPTY_RESPONSE));
                    } catch (...) {

                        // if couldn't write, then closing the socket
                        try {
                            closeSock(clientSocket);
                        } catch (...) {}

                        return;
                    }

                    // reading the inpput, also with timeout
                    std::string problemString;

                    finished = false;
                    timedout = false;

                    try {
                        // waiting for the client message in a different thread
                        std::thread readThread(readSockTrigger, std::ref(*this),  clientSocket, std::ref(problemString), std::ref(finished));
                        // counting the timeout
                        timeout(finished, timedout);

                        readThread.join();

                        // if the timeout hasn't been reached, then the client hasn't connected in the last 5 seconds,
                        // so closing the connection
                        if(timedout){
                            try{
                                closeSock(clientSocket);
                            } catch (...){}
                                return;
                        }

                    } catch (const status_exception::StatusException& e) {
                        // if couldn't read from the socket, then sending error log and closing the connection
                        try {
                            writeSock(clientSocket, getLog(s_VERSION, e.getStatus(), s_EMPTY_RESPONSE));
                        } catch (...) {}

                        try {
                            closeSock(clientSocket);
                        } catch (...) {}

                        return;
                    }

                    // success in recieving input, solving the problem with the input.
                    // this variable will hold the solution, as string
                    std::string solutionString;
                    // this variable will hold the status of the solving
                    uint32_t status = 0;

                    // first, searching for the solution in the cache:
                    // getting the hashCode of the operation
                    const uint32_t hashCode = util::HashUtil::calculateHash(commandString + problemString);
                    // if the operation result also exists in the cache, so getting it from the cache
                    if (m_cacheManager.contains(hashCode)) {
                        try {
                            solutionString = m_cacheManager.getOperationFileContent(hashCode);
                            // loading the operation into the cache
                            m_cacheManager.load(operation::SolverOperation(hashCode, solutionString));
                        } catch (...) {
                            status = 5;
                        }

                    } else {
                        try {
                            const auto solver = m_commandParser->parse(commandString);
                            const auto problem = m_inputParser->parse(problemString);
                            solutionString = solver->solve(problem).toString();
                            // loading the operation into the cache
                            m_cacheManager.load(operation::SolverOperation(hashCode, solutionString));
                        } catch(const status_exception::StatusException& e){
                            status = e.getStatus();
                        } catch (...) {
                            status = 5;
                        }
                    }

                    // the calculation has succeeded
                    if (status == 0) {
                        // sending a success message
                        try {
                            writeSock(clientSocket, getLog(s_VERSION, status, solutionString) + "\r\n");
                        } catch (...) {}

                        try {
                            closeSock(clientSocket);
                        } catch (...) {}
                    }
                    // if the calculation has failed
                    else {
                        // sending a error message
                        try {
                            writeSock(clientSocket, getLog(s_VERSION, status, s_EMPTY_RESPONSE) + "\r\n");
                        } catch (...) {}

                        try {
                            closeSock(clientSocket);
                        } catch (...) {}
                    }         
                }

            private:

                /**
                 * @brief Read the content from the socket, and also mark the reading as completed.
                 *      used for the thread.
                 * 
                 * @param ch the given solver client handler
                 * @param clientSocket the given client socket
                 * @param message a variable that will be initialized with the message sent to the socket
                 * @param finished this variable will be initialized with true if the reading from the socket is completed
                 */
                static void readSockTrigger(const SolverClientHandler<Problem, Solution>& ch, const uint32_t clientSocket, std::string& message, bool& finished){
                    message = ch.readSock(clientSocket);
                    finished = true;
                }

                /**
                 * @brief Getting if the timeout has been reached, according to a boolean variable
                 * 
                 * @param finished holding true if the operation that we are waiting to has been finished
                 * @param timeout holding true if the timeout has been reached
                 */
                void timeout(bool& finished, bool& timeout) const{
                    auto start = std::chrono::high_resolution_clock::now();
                    while(true){   
                        auto time = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(time - start);
                        if(duration.count() > 5000000){
                            timeout = true;
                            return;
                        }
                        if(finished){
                            timeout = false;
                            return;
                        }
                    }
                }
        };
    }
}