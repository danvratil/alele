// SPDX-FileCopyrightText: 2021 Daniel Vrátil <dvratil@kde.org>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#pragma once

#include "error.h"

#include <tl/expected.hpp>

namespace Alele {

template<typename T, typename E = Alele::Error>
using Expected = tl::expected<T, E>;

using namespace tl;

} // namespce Alele
