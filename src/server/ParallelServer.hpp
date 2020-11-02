#pragma once

#include "Server.hpp"

#include <queue>
#include <vector>
#include <thread>
#include <mutex>

namespace server_side
{   
    /**
     * @brief This class represents a parallel server.
     * 
     */
    class ParallelServer : public Server
    {

        // the backlog size of the server
        const uint32_t m_backlog = 100;
        // the thread pool size of the server
        const uint32_t m_threadPoolSize = 20;
        // queue with the waiting clients
        mutable std::queue<uint32_t> m_waitingClients;
        // thread pool
        mutable std::vector<std::thread> m_threadPool;

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

    private:
        /**
            * @brief Handle the clients in the queue.
            *       used for the thread.
            * 
            * @param mutexLock the given mutex lock
            * @param waitingClients the given queue with waiting clients
            * @param ch the given client handler
         */
        static void clientHandle(std::mutex &mutexLock, std::queue<uint32_t> &waitingClients, const client_handler::ClientHandler &ch);
    };
}
