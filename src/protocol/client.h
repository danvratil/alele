// SPDX-FileCopyrightText: 2021 Daniel Vrátil <dvratil@kde.org>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#pragma once

#include "common/id.h"

#include <msgpack.hpp>

#include <string>
#include <optional>

namespace Alele::ClientProtocol {

enum class MessageType {
    ErrorResponse,
    CreateDirectory,
    Directory
};

struct Directory {
    Alele::Id id;
    Alele::Id parentId;
    std::string name;

    MSGPACK_DEFINE(id, parentId, name)
};

struct ErrorResponse {
    std::string error_msg;

    MSGPACK_DEFINE(error_msg)
};

struct CreateDirectory {
    Alele::Id parentId;
    std::string name;

    MSGPACK_DEFINE(parentId, name)
};

} // namespace Alele::ClientProtocol

MSGPACK_ADD_ENUM(Alele::ClientProtocol::MessageType)
