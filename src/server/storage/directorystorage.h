// SPDX-FileCopyrightText: 2021 Daniel Vrátil <dvratil@kde.org>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#pragma once

#include "common/id.h"
#include "common/directory.h"
#include "common/expected.h"

#include <qcoro/task.h>

namespace Alele::Server {

class DirectoryStorage
{
public:
    explicit DirectoryStorage();

    QCoro::Task<Expected<Directory>> fetchOne(Id id);

    QCoro::Task<Expected<Directories>> fetchAll();
};

} // namespace Alele::Server

#ifdef UNIT_TESTS

#include <gmock/gmock.h>

namespace Alele::Server {

class MockDirectoryStorage {
public:
    MOCK_METHOD(QCoro::Task<Expected<Directory>>, fetchOne, (Id), ());
    MOCK_METHOD(QCoro::Task<Expected<Directories>>, fetchAll, (), ());
};

} // namespace Alele::Server

#endif
