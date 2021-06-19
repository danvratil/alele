// SPDX-FileCopyrightText: 2021 Daniel Vrátil <dvratil@kde.org>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#include "common/id.h"

#include <gtest/gtest.h>

#include <sstream>

TEST(Id, comparison) {
    {
        Alele::Id id1{'E', 42};
        Alele::Id id2{'E', 42};
        EXPECT_EQ(id1, id2);
        EXPECT_FALSE(id1 < id2);
        EXPECT_FALSE(id1 > id2);
        EXPECT_FALSE(id1 != id2);
    }

    {
        Alele::Id id1{'E', 42};
        Alele::Id id2{'F', 42};
        EXPECT_NE(id1, id2);
        EXPECT_FALSE(id1 < id2);
        EXPECT_GT(id1, id2);
        EXPECT_FALSE(id1 == id2);
    }
}

TEST(Id, serialization) {
    std::stringstream stream;

    Alele::Id in('E', 42);
    msgpack::pack(stream, in);

    msgpack::object_handle handle;
    msgpack::unpack(handle, stream.str().c_str(), stream.str().size());
    EXPECT_EQ(in, handle->as<Alele::Id>());
}
