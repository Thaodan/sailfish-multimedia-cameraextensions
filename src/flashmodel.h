/*
  SPDX-FileCopyrightText: Copyright (C) 2021 Jolla Ltd. (bjorn.bidar@jolla.com)
  SPDX-FileCopyrightText: Copyright (C) 2019 Adam Pigg (adam@piggz.co.uk)

  SPDX-License-Identifier: LGPL-2.1-or-later

  -*- mode: c++ -*-
*/

#ifndef FLASHMODEL_H
#define FLASHMODEL_H

#include <QAbstractListModel>
#include <QCamera>
#include <QPair>

#include <sfmultimediacameraextensions/SFMultimediaCameraExtensions_export.h>

namespace SFMultimediaCameraExtensions {

    class FlashModelPrivate;
    class SFMULTIMEDIACAMERAEXTENSIONS_EXPORT FlashModel : public QAbstractListModel
    {
        Q_OBJECT
        Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged)

    public:

        enum FlashRoles {
            FlashName = Qt::UserRole + 1,
            FlashValue
        };

        explicit FlashModel(QObject *parent = nullptr);
        ~FlashModel() override;

        QHash<int, QByteArray> roleNames() const override;
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role) const override;

        Q_INVOKABLE void setCamera(QObject *camera);

    private:
        FlashModelPrivate *const d_ptr;
        Q_DECLARE_PRIVATE(FlashModel);

        QString flashName(QCameraExposure::FlashMode flash) const;

    signals:
        void rowCountChanged();
    };
}

#endif // FOCUSMODEL_H
