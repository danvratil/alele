#pragma once

#include "common/zeromq.h"

namespace Alele::Server {

class Worker {
public:
    explicit Worker(ZMQ::Context &brokerContext)
        : mSocket(brokerContext, ZMQ::SocketType::Rep)
    {}

    void connectToBroker() {
        mSocket.connect("inproc://alele-backend");
    }

    void run() {
        while (true) {
            const auto msg = co_await mSocket.recv();
        }
    }

private:
    ZMQ::Socket mSocket;
};

} // namespace Alele::Server
