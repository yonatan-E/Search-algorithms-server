#include "ServerFactory.hpp"
#include "SerialServer.hpp"
#include "ParallelServer.hpp"

namespace server_side {

    ServerFactory::ServerFactory() {
        m_map.emplace("serial", [](){return std::make_unique<SerialServer>();});
        m_map.emplace("parallel", [](){return std::make_unique<ParallelServer>();});
    }

    std::unique_ptr<Server> ServerFactory::getServer(const std::string& type) const {
        if (m_map.find(type) == m_map.end()) {
            return nullptr;
        }
        return m_map.at(type)();
    }

    std::unique_ptr<Server> ServerFactory::getDefaultServer() const {
        return getServer("parallel");
    }
}  