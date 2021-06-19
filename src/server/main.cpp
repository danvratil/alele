// SPDX-FileCopyrightText: 2021 Daniel Vrátil <dvratil@kde.org>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#include "storage.h"
#include "workermanager.h"

using namespace Alele;
using namespace Alele::Server;

#if 0
const char *getFrontendSocketBind() {
    return "ipc://@alele-frontend";
}

const char *getBackendSocketBind() {
    return "inproc://alele-backend";
}

void runBroker(ZMQ::Socket &frontendSocket, ZMQ::Socket &backendSocket) {
    zmq_proxy(frontendSocket.get(), backendSocket.get(), nullptr);
}
#endif

int main(int argc, char **argv) {
    // TODO: single-instance application (use DBus)


    // Make sure our storage is ready
    auto storage = Storage::init();
    if (storage->needsUpgrade()) {
        // Starts async DB upgrade in the background. We continue with start-up, so that clients
        // can connect and show the "Upgrading" screen
        storage->startUpgrade();
    }

#if 0
    ZMQ::Context brokerContext;
    ZMQ::Socket frontendSocket{brokerContext, ZMQ::SocketType::Router};
    ZMQ::Socket backendSocket{brokerContext, ZMQ::SocketType::Dealer};
    if (!frontendSocket.bind(getFrontendSocketBind())) {
        return 1;
    }
    if(!backendSocket.bind(getBackendSocketBind())) {
        return 1;
    }

    auto workerManager = WorkerManager::init(brokerContext);
    workerManager->start();

    // Blocks and runs an event loop that forwards stuff from frontend
    // to backend
    runBroker(frontendSocket, backendSocket);

#endif
    return 0;
}
