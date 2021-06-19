// SPDX-FileCopyrightText: 2021 Daniel Vrátil <dvratil@kde.org>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#pragma once

#include <memory>

#include "storage/directorystorage.h"

namespace Alele::Server {

class Storage
{
public:
    DirectoryStorage &directories();

private:
    DirectoryStorage m_directoryStorage;
};

} // namespace Alele::Server

#ifdef UNIT_TESTS

#include <gmock/gmock.h>

namespace Alele::Server {

class MockStorage
{
public:
    MockDirectoryStorage &directories();

private:
    MockDirectoryStorage m_directoryStorage;
};

} // namespace Alele::Server

#endif
