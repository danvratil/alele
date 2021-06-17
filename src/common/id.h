// SPDX-FileCopyrightText: 2021 Daniel Vrátil <dvratil@kde.org>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#pragma once

#include <msgpack.hpp>

#include <compare>
#include <functional>
#include <cstdint>

namespace Alele {
struct Id;
} // namespace Alele

namespace std {
    template<>
    struct hash<Alele::Id> {
        size_t operator()(const Alele::Id id) const;
    };
} // namespace std

namespace msgpack::adaptor {
    template<>
    struct convert<Alele::Id> {
        const msgpack::object &operator()(const msgpack::object &obj, Alele::Id &id) const;
    };

    template<>
    struct pack<Alele::Id> {
        template<typename Stream>
        msgpack::packer<Stream> &operator()(msgpack::packer<Stream> &, const Alele::Id id) const;
    };
} // namespace msgpack::adaptor

namespace Alele {

struct Id {
    constexpr Id() = default;

    constexpr Id(char c, std::uint32_t i)
        : m_val(static_cast<decltype(m_val)>(c) << 63U | i)
    {}
    constexpr Id(uint64_t val)
        : m_val(val)
    {}

    Id(const Id &) = default;
    Id(Id &&) noexcept = default;
    Id &operator=(const Id &) = default;
    Id &operator=(Id &&) noexcept = default;
    auto operator<=>(const Id &) const = default;

    constexpr bool isValid() const { return m_val > 0; }

private:
    uint64_t m_val = 0;

    friend std::hash<Id>;
    friend msgpack::adaptor::convert<Id>;
    friend msgpack::adaptor::pack<Id>;
};

} // namespace Alele

namespace std {

size_t hash<Alele::Id>::operator()(const Alele::Id id) const {
    return std::hash<uint64_t>{}(id.m_val);
}

} // namespace std

namespace msgpack::adaptor {

const msgpack::object &convert<Alele::Id>::operator()(const msgpack::object &obj, Alele::Id &id) const {
    if (obj.type != msgpack::type::POSITIVE_INTEGER) {
        throw msgpack::type_error{};
    }
    id.m_val = obj.as<uint64_t>();
    return obj;
}

template<typename Stream>
msgpack::packer<Stream> &pack<Alele::Id>::operator()(msgpack::packer<Stream> &o, Alele::Id id) const {
    o.pack(id.m_val);
    return o;
}
} // namespace msgpack::adaptor
