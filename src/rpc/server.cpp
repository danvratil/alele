// SPDX-FileCopyrightText: 2021 Daniel Vrátil <dvratil@kde.org>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#include "server.h"

using namespace Alele::RPC;

Server::Server(std::string_view endpoint)
    : m_socket{m_context, ZMQ::SocketType::Router}
{
    m_socket.bind(endpoint);
}

Server::~Server()
{
    if (m_thread.joinable()) {
        m_thread.join();
    }
}

void Server::run()
{
    m_thread = std::thread{[this]() {
        ZMQ::Message msg;
        m_socket.recv(msg.get());
        msg.more();
    }};
}



