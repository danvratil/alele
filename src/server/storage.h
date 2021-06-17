#pragma once

#include <memory>

namespace Alele::Server {

class Storage
{
public:
    static std::unique_ptr<Storage> init() {
        return std::make_unique<Storage>();
    }

    bool needsUpgrade() const { return false; };
    void startUpgrade() {};
};

} // namespace Server
