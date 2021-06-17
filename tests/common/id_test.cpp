// SPDX-FileCopyrightText: 2021 Daniel Vrátil <dvratil@kde.org>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#include "common/id.h"

#include <catch2/catch.hpp>

#include <sstream>

TEST_CASE("Id::comparison", "[common][id]") {

    {
        Alele::Id id1{'E', 42};
        Alele::Id id2{'E', 42};
        REQUIRE(id1 == id2);
        REQUIRE_FALSE(id1 < id2);
        REQUIRE_FALSE(id1 > id2);
        REQUIRE_FALSE(id1 != id2);
    }

    {
        Alele::Id id1{'E', 42};
        Alele::Id id2{'F', 42};
        REQUIRE(id1 != id2);
        REQUIRE_FALSE(id1 < id2);
        REQUIRE(id1 > id2);
        REQUIRE_FALSE(id1 == id2);
    }
}

TEST_CASE("Id::serialize", "[common][id]") {
    std::stringstream stream;

    Alele::Id in('E', 42);
    msgpack::pack(stream, in);

    msgpack::object_handle handle;
    msgpack::unpack(handle, stream.str().c_str(), stream.str().size());
    REQUIRE(in == handle->as<Alele::Id>());
}
