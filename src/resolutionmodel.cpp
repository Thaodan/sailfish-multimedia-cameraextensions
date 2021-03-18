/*
  SPDX-FileCopyrightText: Copyright (C) Jolla Ltd. (bjorn.bidar@jolla.com)
  SPDX-FileCopyrightText: Copyright (C) 2019 Adam Pigg (adam@piggz.co.uk)

  SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "resolutionmodel.h"

using namespace SFMultimediaCameraExtensions;

class SFMultimediaCameraExtensions::ResolutionModelPrivate
{

public:
    QMap<QString, QSize> m_resolutions;
    QList<QSize> m_supportedImageResolutions;
    QList<QSize> m_supportedVideoResolutions;
    QString m_mode = "image";
};


ResolutionModel::ResolutionModel(QObject *parent)
    : QAbstractListModel(parent)
    , d_ptr(new ResolutionModelPrivate)
{
}

ResolutionModel::~ResolutionModel()
{
    Q_D(ResolutionModel);
    delete d;
}


QHash<int, QByteArray> ResolutionModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ResolutionName] = "name";
    roles[ResolutionValue] = "value";
    return roles;
}

int ResolutionModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    Q_D(const ResolutionModel);
    return d->m_resolutions.count();
}

QVariant ResolutionModel::data(const QModelIndex &index, int role) const
{
    Q_D(const ResolutionModel);
    QVariant v;

    if (!index.isValid() || index.row() > rowCount(index) || index.row() < 0) {
        return v;
    }

    if (role == ResolutionName) {
        QSize r = sizeToRatio(d->m_resolutions.values().at(index.row()));
        v = d->m_resolutions.keys().at(index.row()) + QString(" (%1:%2)").arg(r.width()).arg(r.height());
    } else if (role == ResolutionValue) {
        v = d->m_resolutions.values().at(index.row());
    } else if (role == ResolutionMpx) {
        v = d->m_resolutions.values().at(index.row()).width() * d->m_resolutions.values().at(
                index.row()).height();
    }
    return v;
}

void ResolutionModel::setImageCapture(QObject *capture)
{
    Q_D(ResolutionModel);
    QCameraImageCapture *cap = nullptr;
    QList<QCameraImageCapture *> captures = capture->findChildren<QCameraImageCapture *>();

    if (captures.count() > 0) {
        cap = captures[0]; //first will do!
    }

    if (cap) {
        d->m_supportedImageResolutions = cap->supportedResolutions();
        if (!d->m_mode.isEmpty()) {
            setMode(d->m_mode);
        }
    }
}

void ResolutionModel::setVideoRecorder(QObject *capture)
{
    Q_D(ResolutionModel);
    QMediaRecorder *cap = nullptr;
    QList<QMediaRecorder *> captures = capture->findChildren<QMediaRecorder *>();

    if (captures.count() > 0) {
        cap = captures[0]; //first will do!
    }

    if (cap) {
        d->m_supportedVideoResolutions = cap->supportedResolutions();
        if (!d->m_mode.isEmpty()) {
            setMode(d->m_mode);
        }
    }
}

void ResolutionModel::setMode(const QString &mode)
{
    Q_D(ResolutionModel);
    d->m_mode = mode;
    beginResetModel();
    d->m_resolutions.clear();

    if (mode == "image") {
        for (int i = 0; i < d->m_supportedImageResolutions.count() ; i++) {
            d->m_resolutions[QString("%1x%2").arg(d->m_supportedImageResolutions[i].width()).arg(
                              d->m_supportedImageResolutions[i].height())] = d->m_supportedImageResolutions[i];
        }
    } else if (mode == "video") {
        for (int i = 0; i < d->m_supportedVideoResolutions.count() ; i++) {
            d->m_resolutions[QString("%1x%2").arg(d->m_supportedVideoResolutions[i].width()).arg(
                              d->m_supportedVideoResolutions[i].height())] = d->m_supportedVideoResolutions[i];
        }
    }

    endResetModel();
    emit rowCountChanged();

    if (d->m_resolutions.size() > 0) {
        qDebug() << "Supported " << mode << " resolutions:" << d->m_resolutions;
    } else {
        qWarning() << "No resolutions found";
    }
}

QSize ResolutionModel::defaultResolution(const QString &mode)
{
    Q_D(ResolutionModel);
    if (mode == "video") {
        if (d->m_supportedVideoResolutions.count() > 0) {
            return d->m_supportedVideoResolutions.at(d->m_supportedVideoResolutions.count() - 1);
        }
    } else if (mode == "image") {
        if (d->m_supportedImageResolutions.count() > 0) {
            return d->m_supportedImageResolutions.at(d->m_supportedImageResolutions.count() - 1);
        }
    }
    return QSize(0, 0);
}

bool ResolutionModel::isValidResolution(const QSize &resolution, const QString &mode)
{
    Q_D(ResolutionModel);
    if (mode == "image") {
        return d->m_supportedImageResolutions.contains(resolution);
    } else if (mode == "video") {
        return d->m_supportedVideoResolutions.contains(resolution);
    }
    return false;
}

QSize ResolutionModel::sizeToRatio(const QSize &siz) const
{
    int a = siz.width();
    int b = siz.height();
    int c = a % b;
    int gcd = 0;

    while (c > 0) {
        a = b;
        b = c;
        c = a % b;
    }

    gcd = b;
    return siz / gcd;
}
