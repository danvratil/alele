// SPDX-FileCopyrightText: 2021 Daniel Vrátil <dvratil@kde.org>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#pragma once

#include <zmq.h>

#include <memory>
#include <iostream>
#include <string_view>
#include <cstring>
#include <vector>

namespace Alele::ZMQ {

class Context
{
public:
    explicit Context()
        : mCtx(zmq_ctx_new(), &zmq_ctx_destroy)
    {}

    void *get() {
        return mCtx.get();
    }

private:
    std::unique_ptr<void, decltype(&zmq_ctx_destroy)> mCtx;
};

enum class SocketType {
    Pair = ZMQ_PAIR,
    Pub = ZMQ_PUB,
    Sub = ZMQ_SUB,
    Req = ZMQ_REQ,
    Rep = ZMQ_REP,
    Dealer = ZMQ_DEALER,
    Router = ZMQ_ROUTER,
    Pull = ZMQ_PULL,
    Push = ZMQ_PUSH,
    XPub = ZMQ_XPUB,
    XSub = ZMQ_XSUB,
    Stream = ZMQ_STREAM
};

class Message
{
public:
    explicit Message() {
        zmq_msg_init(&msg);
    }
    
    explicit Message(const std::vector<uint8_t> &data) {
        zmq_msg_init_data(&msg, const_cast<uint8_t *>(data.data()), data.size(), nullptr, nullptr);
    }

    ~Message() {
        zmq_msg_close(&msg);
    }

    zmq_msg_t *get() {
        return &msg;
    }

    bool more() const {
        return static_cast<bool>(zmq_msg_more(&msg));
    }

    std::size_t size() const {
        return zmq_msg_size(&msg);
    }

    void *data() {
        return zmq_msg_data(&msg);
    }

private:
    zmq_msg_t msg;
};

class Socket
{
public:
    explicit Socket(Context &context, SocketType socketType)
        : mSocket(zmq_socket(context.get(), static_cast<int>(socketType)), zmq_close)
    {}

    bool bind(std::string_view endpoint) {
        if (zmq_bind(mSocket.get(), endpoint.data()) < 0) {
            const auto errnosnapshot = errno;
            std::cerr << "Error when binding ZMQ socket to endpoint " << endpoint << ": " << strerror(errnosnapshot) << std::endl;
            return false;
        }

        return true;
    }

    bool connect(std::string_view endpoint) {
        if (zmq_connect(mSocket.get(), endpoint.data()) < 0) {
            const auto errnosnapshot = errno;
            std::cerr << "Failed to connect ZMQ socket to endpoint " << endpoint << ": " << strerror(errnosnapshot) << std::endl;
            return false;
        }

        return true;
    }

    void recv(zmq_msg_t *msg) {
        zmq_msg_init(msg);
        zmq_msg_recv(msg, mSocket.get(), 0);
    }

    void *get() {
        return mSocket.get();
    }

private:
    std::unique_ptr<void, decltype(&zmq_close)> mSocket;
};

} // namespace Alele::ZMQ
