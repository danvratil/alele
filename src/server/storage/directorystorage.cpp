// SPDX-FileCopyrightText: 2021 Daniel Vrátil <dvratil@kde.org>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#include "directorystorage.h"

using namespace Alele;
using namespace Alele::Server;

DirectoryStorage::DirectoryStorage()
{
}

QCoro::Task<Expected<Directory>> DirectoryStorage::fetchOne(Id id)
{
    // hmmm?
}

QCoro::Task<Expected<Directories>> DirectoryStorage::fetchAll()
{
    // hmmmmmmmmm
}
