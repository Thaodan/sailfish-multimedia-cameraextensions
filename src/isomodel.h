/*
  SPDX-FileCopyrightText: Copyright (C) 2021 Jolla Ltd. (bjorn.bidar@jolla.com)
  SPDX-FileCopyrightText: Copyright (C) 2019 Adam Pigg (adam@piggz.co.uk)

  SPDX-License-Identifier: LGPL-2.1-or-later

  -*- mode: c++ -*-
*/

#ifndef ISOMODEL_H
#define ISOMODEL_H

#include <QAbstractListModel>
#include <QCamera>
#include <QPair>

#include <sfmultimediacameraextensions/SFMultimediaCameraExtensions_export.h>

namespace SFMultimediaCameraExtensions {

    class IsoModelPrivate;
    class SFMULTIMEDIACAMERAEXTENSIONS_EXPORT IsoModel : public QAbstractListModel
    {
        Q_OBJECT
        Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged)

    public:

        enum IsoRoles {
            IsoName = Qt::UserRole + 1,
            IsoValue
        };

        explicit IsoModel(QObject *parent = nullptr);
        ~IsoModel() override;

        QHash<int, QByteArray> roleNames() const override;
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role) const override;

        Q_INVOKABLE void setCamera(QObject *camera);

    private:
        IsoModelPrivate *const d_ptr;
        Q_DECLARE_PRIVATE(IsoModel);

        QString isoName(int iso) const;

    signals:
        void rowCountChanged();
    };
}
#endif // EFFECTSMODEL_H
