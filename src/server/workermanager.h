#pragma once

#include "worker.h"

#include <memory>
#include <thread>
#include <vector>

namespace Alele::ZMQ {
class Context;
} // namespace Alele::ZMQ

namespace Alele::Server {

class WorkerManager {
public:
    explicit WorkerManager(ZMQ::Context &brokerContext):
        mBrokerContext{brokerContext} {
        mPool.resize(sDefaultWorkerPoolSize);
    }

    static std::unique_ptr<WorkerManager> init(ZMQ::Context &brokerContext) {
        return std::make_unique<WorkerManager>(brokerContext);
    }

    void start() {
        for (auto thread = mPool.begin(), end = mPool.end(); thread != end; ++thread) {
            *thread = startWorker(mBrokerContext);
        }
    }

private:
    std::thread startWorker(ZMQ::Context &brokerContext) {
        return std::thread([&brokerContext]() {
            Worker worker(brokerContext);
            worker.connectToBroker();
            worker.run();
        });
    }

    static constexpr std::size_t sDefaultWorkerPoolSize = 5;

    std::vector<std::thread> mPool;
    ZMQ::Context &mBrokerContext;
};

} // namespace Alele::Server
