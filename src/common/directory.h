// SPDX-FileCopyrightText: 2021 Daniel Vrátil <dvratil@kde.org>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#pragma once

#include "id.h"

#include <QObject>
#include <QString>

#include <vector>

namespace Alele {

//! Describes a single directory inside the tree hierarchy
/*!
 * Each directory has it's own ID, reference to a parent (through \c parentId) and user-friendly name.
 */
class Directory {
    Q_GADGET
    Q_PROPERTY(Alele::Id id READ id WRITE setId)
    Q_PROPERTY(Alele::Id parentId READ parentId WRITE setParentId)
    Q_PROPERTY(QString name READ name WRITE setName)
public:
    explicit Directory() = default;
    explicit Directory(Id id)
        : m_id(id) {}
    Directory(Id id, Id parentId, const QString &name)
        : m_id(id), m_parentId(parentId), m_name(name)
    {}

    bool operator==(const Directory &other) const {
        return m_id == other.m_id;
    }

    //! Gets ID of the directory.
    Id id() const {
        return m_id;
    }

    //! Sets ID of the directory.
    void setId(Id id) {
        m_id = id;
    }

    //! Gets Id of parent directory, or 0 if this directory is a top-level directory.
    Id parentId() const {
        return m_parentId;
    }

    //! Sets ID of the parent directory.
    void setParentID(Id parentId) {
        m_parentId = parentId;
    }

    //! Gets the user-friendly name of the directory.
    QString name() const {
        return m_name;
    }

    //! Sets the user-friendly name of the directory.
    void setName(const QString &name) {
        m_name = name;
    }

private:
    Alele::Id m_id;
    Alele::Id m_parentId;
    QString m_name;
};

using Directories = std::vector<Directory>;

} // namespace Aele
