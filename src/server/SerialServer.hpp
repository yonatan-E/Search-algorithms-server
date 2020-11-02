#pragma once

#include "Server.hpp"

namespace server_side
{
    /**
     * @brief This class represents a serial server.
     * 
     */
    class SerialServer : public Server
    {

        // the backlog size of the serial server
        const uint32_t m_backlog = 100;

    public:
        /**
             * @brief Open the server and run it with a client handler
             * 
             * @param serverPort the given server port
             * @param clientHandler the given client handler, will be used to handle the clients
             */
        void open(uint32_t serverPort, const client_handler::ClientHandler &clientHandler) const override;

        /**
             * @brief Check if the server stop
             * 
             * @return true if the server should stop
             * @return false if the server should not stop
             */
        bool stop() const override;
    };
}
