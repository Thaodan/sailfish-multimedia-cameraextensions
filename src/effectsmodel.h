/*
  SPDX-FileCopyrightText: Copyright (C) 2021 Jolla Ltd. (bjorn.bidar@jolla.com)
  SPDX-FileCopyrightText: Copyright (C) 2019 Adam Pigg (adam@piggz.co.uk)

  SPDX-License-Identifier: LGPL-2.1-or-later

  -*- mode: c++ -*-
*/

#ifndef EFFECTSMODEL_H
#define EFFECTSMODEL_H

#include <QAbstractListModel>
#include <QCamera>
#include <QPair>

#include <sfmultimediacameraextensions/SFMultimediaCameraExtensions_export.h>

namespace SFMultimediaCameraExtensions {

    class EffectsModelPrivate;
    class SFMULTIMEDIACAMERAEXTENSIONS_EXPORT EffectsModel : public QAbstractListModel
    {
        Q_OBJECT
        Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged)

    public:

        enum EffectRoles {
            EffectName = Qt::UserRole + 1,
            EffectValue
        };

        explicit EffectsModel(QObject *parent = nullptr);
        ~EffectsModel() override;

        QHash<int, QByteArray> roleNames() const override;
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role) const override;

        Q_INVOKABLE void setCamera(QObject *camera);

    private:
        EffectsModelPrivate *const d_ptr;
        Q_DECLARE_PRIVATE(EffectsModel);

        QString effectName(QCameraImageProcessing::ColorFilter c) const;

    signals:
        void rowCountChanged();
    };
}

#endif // EFFECTSMODEL_H
