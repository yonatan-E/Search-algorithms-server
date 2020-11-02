#include "ParallelServer.hpp"
#include "ServerExceptions.hpp"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <thread>

namespace server_side
{

    void ParallelServer::open(uint32_t serverPort, const client_handler::ClientHandler &clientHandler) const
    {
        struct sockaddr_in clientAddress;
        struct sockaddr_in serverAddress;

        std::mutex m_mutexLock;

        for (uint32_t i = 0; i < m_threadPoolSize; ++i)
        {
            m_threadPool.push_back(std::thread(clientHandle, std::ref(m_mutexLock), std::ref(m_waitingClients), std::ref(clientHandler)));
        }

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
            // waiting for connections

            uint32_t addrSize = sizeof(clientAddress);

            auto clientSocket = accept(serverSocket, reinterpret_cast<sockaddr *>(&clientAddress), reinterpret_cast<socklen_t *>(&addrSize));

            if (clientSocket < 0)
            {
                throw exceptions::ServerException("Error while accepting a client socket");
            }

            m_waitingClients.push(clientSocket);
        }
    }

    bool ParallelServer::stop() const
    {
        return false;
    }

    void ParallelServer::clientHandle(std::mutex &mutexLock, std::queue<uint32_t> &waitingClients, const client_handler::ClientHandler &ch)
    {
        while (true)
        {
            mutexLock.lock();
            uint32_t currentClient;
            if (waitingClients.size() > 0)
            {
                currentClient = waitingClients.front();
                waitingClients.pop();
                ch.handleClient(currentClient);
            }
            mutexLock.unlock();
        }
    }
}