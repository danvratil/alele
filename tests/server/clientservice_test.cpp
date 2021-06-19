// SPDX-FileCopyrightText: 2021 Daniel Vrátil <dvratil@kde.org>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#include "server/clientservice.h"
#include "server/storage.h"
#include "common/expected.h"
#include "helpers/gmockhelpers.h"

#include <unordered_map>

using namespace Alele;
using namespace Alele::Server;


static const auto testDirectories = std::unordered_map<Id, Directory>{
    {Id{1}, Directory{Id{1}, Id{0}, QStringLiteral("test.account@kde.org")}},
    {Id{2}, Directory{Id{2}, Id{1}, QStringLiteral("Inbox")}},
    {Id{3}, Directory{Id{3}, Id{1}, QStringLiteral("Trash")}},
    {Id{4}, Directory{Id{4}, Id{1}, QStringLiteral("Projects")}},
    {Id{5}, Directory{Id{5}, Id{4}, QStringLiteral("Alele")}},
    {Id{6}, Directory{Id{6}, Id{4}, QStringLiteral("Akonadi")}}
};


CO_TEST(ClientService, fetchDirectory) {
    MockStorage storage;

    EXPECT_CALL(storage.directories(), fetchOne(Id{1}))
        .WillRepeatedly(CoReturn(Expected<Directory>{testDirectories.at(Id{1})}));

    ClientService clientService(storage);

    const auto result = co_await clientService.fetchDirectory(Id{1});
    EXPECT_EQ(result, testDirectories.at(Id{1}));
}

CO_TEST(ClientService, fetchRootDirectoryIsNotAllowed) {
    MockStorage storage;

    EXPECT_CALL(storage.directories(), fetchOne(Id{0})).Times(0);

    ClientService clientService(storage);

    const auto result = co_await clientService.fetchDirectory(Id{0});
    EXPECT_FALSE(static_cast<bool>(result));
}

