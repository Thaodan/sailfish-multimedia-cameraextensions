/*
  SPDX-FileCopyrightText: Copyright (C) 2021 Jolla Ltd. (bjorn.bidar@jolla.com)
  SPDX-FileCopyrightText: Copyright (C) 2019 Adam Pigg (adam@piggz.co.uk)

  SPDX-License-Identifier: LGPL-2.1-or-later

  -*- mode: c++ -*-
*/

#ifndef FOCUSMODEL_H
#define FOCUSMODEL_H

#include <QAbstractListModel>
#include <QCamera>
#include <QPair>

#include <sfmultimediacameraextensions/SFMultimediaCameraExtensions_export.h>

namespace SFMultimediaCameraExtensions {

    class FocusModelPrivate;
    class SFMULTIMEDIACAMERAEXTENSIONS_EXPORT FocusModel : public QAbstractListModel
    {
        Q_OBJECT
        Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged)

    public:

        enum FocusRoles {
            FocusName = Qt::UserRole + 1,
            FocusValue
        };

        explicit FocusModel(QObject *parent = nullptr);
        ~FocusModel() override;

        QHash<int, QByteArray> roleNames() const override;
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role) const override;

        Q_INVOKABLE void setCamera(QObject *camera);

    private:
        QString focusName(QCameraFocus::FocusMode focus) const;
        FocusModelPrivate *const d_ptr;
        Q_DECLARE_PRIVATE(FocusModel);

    signals:
        void rowCountChanged();
    };
}

#endif // FOCUSMODEL_H
