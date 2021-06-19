// SPDX-FileCopyrightText: 2021 Daniel Vrátil <dvratil@kde.org>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#include "clientservice.h"
#include "storage.h"

using namespace Alele;
using namespace Alele::Server;

template<typename _StorageType>
ClientService<_StorageType>::ClientService(_StorageType &storage)
    : m_storage(storage)
{}

template<typename _StorageType>
QCoro::Task<Expected<Directory>> ClientService<_StorageType>::fetchDirectory(Id id)
{
    if (id == 0) {
        co_return unexpected{Error{"Can't fetch the root directory"}};
    }

    co_return co_await m_storage.directories().fetchOne(id);
}

template<typename _StorageType>
QCoro::Task<Expected<Directories>> ClientService<_StorageType>::fetchDirectories(Id rootId)
{
    if (rootId == 0) {
        co_return co_await m_storage.directories().fetchAll();
    }

    // FIXME: Use CTE!
    co_return co_await m_storage.directories().fetchAll();
}

template class ClientService<Storage>;
#ifdef UNIT_TESTS
template class ClientService<MockStorage>;
#endif
