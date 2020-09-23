#pragma once

#include "../solvers/Solver.hpp"

namespace server {

    namespace clientside {

        class ClientHandler{
            
            public:
            
                virtual void handleClient(uint32_t clientSocket) const = 0;
        };
    }
}