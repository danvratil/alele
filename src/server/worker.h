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
        zmq_msg_t msg;
        zmq_msg_init(&msg);
        while (true) {
            mSocket.recv(&msg);
        }
        zmq_msg_close(&msg);
    }

private:
    ZMQ::Socket mSocket;
};

} // namespace Alele::Server
