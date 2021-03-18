/*
  SPDX-FileCopyrightText: Copyright (C) 2021 Jolla Ltd. (bjorn.bidar@jolla.com)
  SPDX-FileCopyrightText: Copyright (C) 2019 Adam Pigg (adam@piggz.co.uk)

  SPDX-License-Identifier: LGPL-2.1-or-later

  -*- mode: c++ -*-
*/

#ifndef WBMODEL_H
#define WBMODEL_H

#include <QAbstractListModel>
#include <QCamera>
#include <QPair>

#include <sfmultimediacameraextensions/SFMultimediaCameraExtensions_export.h>

namespace SFMultimediaCameraExtensions {

    class WhiteBalanceModelPrivate;
    class SFMULTIMEDIACAMERAEXTENSIONS_EXPORT WhiteBalanceModel : public QAbstractListModel
    {
        Q_OBJECT
        Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged)

    public:

        enum WhiteBalanceRoles {
            WhiteBalanceName = Qt::UserRole + 1,
            WhiteBalanceValue
        };

        explicit WhiteBalanceModel(QObject *parent = nullptr);
        ~WhiteBalanceModel() override;

        QHash<int, QByteArray> roleNames() const override;
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role) const override;

        Q_INVOKABLE void setCamera(QObject *camera);

    private:
        WhiteBalanceModelPrivate *const d_ptr;
        Q_DECLARE_PRIVATE(WhiteBalanceModel);

        QString whiteBalanceName(QCameraImageProcessing::WhiteBalanceMode wb) const;

    signals:
        void rowCountChanged();
    };
}

#endif // EFFECTSMODEL_H
