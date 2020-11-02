#include "SerialServer.hpp"
#include "ServerExceptions.hpp"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>

namespace server_side
{

    void SerialServer::open(const uint32_t serverPort, const client_handler::ClientHandler &clientHandler) const
    {

        struct sockaddr_in clientAddress;
        struct sockaddr_in serverAddress;

        const int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket < 0)
        {
            throw exceptions::ServerException("Error while getting a socket");
        }


        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(serverPort);

        if (bind(serverSocket, reinterpret_cast<struct sockaddr *>(&serverAddress), sizeof(serverAddress)) < 0)
        {
            throw exceptions::ServerException("Error while binding the socket to the server");
        }

        if (listen(serverSocket, m_backlog) < 0)
        {
            throw exceptions::ServerException("Error while setting the backlog of the server");
        }

        while (!stop())
        {

            uint32_t addrSize = sizeof(clientAddress);

            const int clientSocket = accept(serverSocket, reinterpret_cast<struct sockaddr *>(&clientAddress),
                                                 reinterpret_cast<socklen_t *>(&addrSize));

            if (clientSocket < 0)
            {
                throw exceptions::ServerException("Error while accepting a client socket");
            }

            // handling the client using the client handler
            clientHandler.handleClient(clientSocket);
        }
    }

    bool SerialServer::stop() const
    {
        return false;
    }
}