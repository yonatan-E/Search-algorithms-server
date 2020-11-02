#pragma once

#include "Server.hpp"

#include <unordered_map>
#include <functional>
#include <memory>

namespace server_side {

    /**
     * @brief This class represents a server factory.
     * 
     */
    class ServerFactory {

        std::unordered_map<std::string, std::function<std::unique_ptr<Server>()>> m_map;

        public:

            /**
             * @brief Construct a new Server Factory object
             * 
             */
            ServerFactory();

            /**
             * @brief Get a server object according to the type of the server
             * 
             * @param type the type of the server
             * @return std::unique_ptr<Server> a pointer to the server object
             */
            std::unique_ptr<Server> getServer(const std::string& type) const;

            /**
             * @brief Get the default server object
             * 
             * @return std::unique_ptr<Server> a pointer to the default server object
             */
            std::unique_ptr<Server> getDefaultServer() const;
    };
}