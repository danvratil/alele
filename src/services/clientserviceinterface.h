// SPDX-FileCopyrightText: 2021 Daniel Vrátil <dvratil@kde.org>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#pragma once

#include "common/expected.h"
#include "common/directory.h"

#include <qcoro/task.h>

#include <QObject>

namespace Alele::Services
{

class ClientServiceInterface {
    Q_GADGET
    Q_CLASSINFO("ServiceName", "alele.client")
    Q_CLASSINFO("ServiceVersion", "1")

public:
    //! Asynchronously fetches a single directory from the server.
    /*!
     *  \param id ID of the directory to fetch.
     *  \return Returns the retrieved directory or an error.
     */
    Q_INVOKABLE virtual
    QCoro::Task<Expected<Directory>> fetchDirectory(Id id) = 0;

    //! Asynchronously fetches part of the directory hierarchy from the server.
    /*!
     * \param rootId ID of the root directory to start retrieving from.
     * \return Returns a list of retrieved directories or an error.
     */
    Q_INVOKABLE virtual
    QCoro::Task<Expected<Directories>> fetchDirectories(Id rootId) = 0;

};

} // namespace Alele::Service

