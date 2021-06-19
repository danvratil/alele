// SPDX-FileCopyrightText: 2021 Daniel Vrátil <dvratil@kde.org>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#include "storage.h"

using namespace Alele::Server;

DirectoryStorage &Storage::directories()
{
    return m_directoryStorage;
}

#ifdef UNIT_TESTS
MockDirectoryStorage &MockStorage::directories()
{
    return m_directoryStorage;
}
#endif
