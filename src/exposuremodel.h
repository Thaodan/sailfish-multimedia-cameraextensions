/*
  SPDX-FileCopyrightText: Copyright (C) 2021 Jolla Ltd. (bjorn.bidar@jolla.com)
  SPDX-FileCopyrightText: Copyright (C) 2019 Adam Pigg (adam@piggz.co.uk)

  SPDX-License-Identifier: LGPL-2.1-or-later

  -*- mode: c++ -*-
*/

#ifndef EXPOSUREMODEL_H
#define EXPOSUREMODEL_H

#include <QAbstractListModel>
#include <QCamera>
#include <QPair>

#include <sfmultimediacameraextensions/SFMultimediaCameraExtensions_export.h>

namespace SFMultimediaCameraExtensions {

    class ExposureModelPrivate;
    class SFMULTIMEDIACAMERAEXTENSIONS_EXPORT ExposureModel : public QAbstractListModel
    {
        Q_OBJECT
        Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged)

    public:

        enum ExposureRoles {
            ExposureName = Qt::UserRole + 1,
            ExposureValue
        };

        explicit ExposureModel(QObject *parent = nullptr);
        ~ExposureModel() override;

        QHash<int, QByteArray> roleNames() const override;
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role) const override;

        Q_INVOKABLE void setCamera(QObject *camera);
        Q_INVOKABLE QString iconName(QCameraExposure::ExposureMode e) const;

    private:
        ExposureModelPrivate *const d_ptr;
        Q_DECLARE_PRIVATE(ExposureModel);

        QString exposureName(QCameraExposure::ExposureMode e) const;

    signals:
        void rowCountChanged();
    };
}

#endif // EFFECTSMODEL_H
