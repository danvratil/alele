// SPDX-FileCopyrightText: 2021 Daniel Vrátil <dvratil@kde.org>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#pragma once

#include "services/clientserviceinterface.h"

namespace Alele::Server {

class Storage;

template<typename _StorageType>
class ClientService : public Services::ClientServiceInterface {
public:
    using StorageType = _StorageType;

    explicit ClientService(StorageType &storage);

    QCoro::Task<Expected<Directory>> fetchDirectory(Id id) override;
    QCoro::Task<Expected<Directories>> fetchDirectories(Id rootId) override;

private:
    StorageType &m_storage;
};

} // namespace Alele::Server
