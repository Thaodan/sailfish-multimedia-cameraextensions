/*
  SPDX-FileCopyrightText: Copyright (C) 2021 Jolla Ltd. (bjorn.bidar@jolla.com)
  SPDX-FileCopyrightText: Copyright (C) 2019 Adam Pigg (adam@piggz.co.uk)

  SPDX-License-Identifier: LGPL-2.1-or-later

-*- mode: c++ -*-
*/

#ifndef RESOLUTIONMODEL_H
#define RESOLUTIONMODEL_H

#include <QAbstractListModel>
#include <QCameraImageCapture>
#include <QMediaRecorder>
#include <QPair>

#include <sfmultimediacameraextensions/SFMultimediaCameraExtensions_export.h>

namespace SFMultimediaCameraExtensions {

    class ResolutionModelPrivate;

    class SFMULTIMEDIACAMERAEXTENSIONS_EXPORT ResolutionModel : public QAbstractListModel
    {
        Q_OBJECT
        Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged)

    public:

        enum ResolutionRoles {
            ResolutionName = Qt::UserRole + 1,
            ResolutionValue,
            ResolutionMpx
        };

        explicit ResolutionModel(QObject *parent = nullptr);
        ~ResolutionModel() override;

        QHash<int, QByteArray> roleNames() const override;
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role) const override;

        Q_INVOKABLE QSize sizeToRatio(const QSize &siz) const;
        Q_INVOKABLE void setImageCapture(QObject *camera);
        Q_INVOKABLE void setVideoRecorder(QObject *capture);
        Q_INVOKABLE void setMode(const QString &mode);
        Q_INVOKABLE QSize defaultResolution(const QString &mode);
        Q_INVOKABLE bool isValidResolution(const QSize &resolution, const QString &mode);

    private:
         ResolutionModelPrivate *const d_ptr;
         Q_DECLARE_PRIVATE(ResolutionModel)

    signals:
        void rowCountChanged();
    };
}
#endif // RESOLUTIONMODEL_H
