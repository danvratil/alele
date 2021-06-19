// SPDX-FileCopyrightText: 2021 Daniel Vrátil <dvratil@kde.org>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#pragma once

#include "zeromq.h"

#include <string_view>
#include <thread>

class QObject;

namespace Alele::RPC {

class Server {
public:
    explicit Server(std::string_view endpoint);
    ~Server();

    void run();
    void stop();

    void registerService(QObject *serviceObject);
    void unregisterService(QObject *serviceObject);

private:
    ZMQ::Context m_context;
    ZMQ::Socket m_socket;
    std::thread m_thread;
};

} // namespace Alele::RPc
