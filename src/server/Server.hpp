#pragma once

#include "SolverClientHandler.hpp"

namespace server_side
{

    /**
     * @brief This class represents a server.
     * 
     */
    class Server
    {

    public:
        /**
             * @brief Open the server and run it with a client handler
             * 
             * @param serverPort the given server port
             * @param clientHandler the given client handler, will be used to handle the clients
             */
        virtual void open(uint32_t serverPort, const client_handler::ClientHandler &clientHandler) const = 0;

        /**
             * @brief Check if the server stop
             * 
             * @return true if the server should stop
             * @return false if the server should not stop
             */
        virtual bool stop() const = 0;

        /**
         * @brief Virtual destructor
         * 
         */
        virtual ~Server() = default;
    };
}