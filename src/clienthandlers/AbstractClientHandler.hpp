#pragma once

#include "ClientHandler.hpp"

#include <string>

namespace server_side {

    namespace client_handler {

        /**
         * @brief This class is a base class for some client handlers.
         * 
         */
        class AbstractClientHandler : public ClientHandler {

            // the size of the buffer used for reading from the socket
            static constexpr int s_BUFFER_SIZE = 65536;

            public:
                
                /**
                 * @brief Handle a specific client
                 * 
                 * @param clientSocket the client socket
                 */
                virtual void handleClient(uint32_t clientSocket) const = 0;

                /**
                 * @brief Virtual destructor
                 * 
                 */
                virtual ~AbstractClientHandler() = default;

            protected:

                /**
                 * @brief Read the content of a client socket
                 * 
                 * @param clientSocket the given client socket
                 * @return std::string a string with the content of the client socket
                 */
                virtual std::string readSock(uint32_t clientSocket) const;

                /**
                 * @brief Write content to a client socket
                 * 
                 * @param clientSocket the given client socket
                 * @param message the content to write to the client socket, as string
                 */
                virtual void writeSock(uint32_t clientSocket, const std::string& message) const;

                /**
                 * @brief Close the connection to a client socket
                 * 
                 * @param clientSocket the given client socket
                 */
                virtual void closeSock(uint32_t clientSocket) const;

                /**
                 * @brief Create a log, and get its string representation
                 * 
                 * @param version the current version
                 * @param status the status of the log
                 * @param message the message of the log
                 * @return std::string string representation of the log
                 */
                std::string getLog(uint32_t version, uint32_t status, const std::string& message) const;
        };
    }
}