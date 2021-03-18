/*
  SPDX-FileCopyrightText: Copyright (C) 2021 Jolla Ltd. (bjorn.bidar@jolla.com)
  SPDX-FileCopyrightText: Copyright (C) 2019 Adam Pigg (adam@piggz.co.uk)

  SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "whitebalancemodel.h"

using namespace SFMultimediaCameraExtensions;

class SFMultimediaCameraExtensions::WhiteBalanceModelPrivate
{
public:
    QMap<int, QString> m_wbModes;
    QCamera *m_camera = nullptr;
};

WhiteBalanceModel::WhiteBalanceModel(QObject *parent)
    : QAbstractListModel(parent)
    , d_ptr(new WhiteBalanceModelPrivate)
{
}

WhiteBalanceModel::~WhiteBalanceModel()
{
    Q_D(WhiteBalanceModel);
    delete d;
}

QHash<int, QByteArray> WhiteBalanceModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[WhiteBalanceName] = "name";
    roles[WhiteBalanceValue] = "value";
    return roles;
}

int WhiteBalanceModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    Q_D(const WhiteBalanceModel);
    return d->m_wbModes.count();
}

QVariant WhiteBalanceModel::data(const QModelIndex &index, int role) const
{
    QVariant v;
    Q_D(const WhiteBalanceModel);

    if (!index.isValid() || index.row() > rowCount(index) || index.row() < 0) {
        return v;
    }

    if (role == WhiteBalanceName) {
        v = d->m_wbModes.values().at(index.row());
    } else if (role == WhiteBalanceValue) {
        v = d->m_wbModes.keys().at(index.row());
    }

    return v;
}

void WhiteBalanceModel::setCamera(QObject *camera)
{
    Q_D(WhiteBalanceModel);

    QCamera *cam = camera->property("mediaObject").value<QCamera *>();
    if (d->m_camera != cam) {
        d->m_camera = cam;

        beginResetModel();
        for (int c = (int)QCameraImageProcessing::WhiteBalanceAuto;
                c <= (int)QCameraImageProcessing::WhiteBalanceWarmFluorescent; c++) {
            if (d->m_camera->imageProcessing()->isWhiteBalanceModeSupported((QCameraImageProcessing::WhiteBalanceMode)c)) {
                qDebug() << "Found support for" << (QCameraImageProcessing::WhiteBalanceMode)c;
                d->m_wbModes[(QCameraImageProcessing::WhiteBalanceMode)c] = whiteBalanceName((QCameraImageProcessing::WhiteBalanceMode)c);
            }
        }
        endResetModel();
        emit rowCountChanged();

        if (d->m_wbModes.size() == 0) {
            qDebug() << "No white balance modes found";
        }
    }
}

QString WhiteBalanceModel::whiteBalanceName(QCameraImageProcessing::WhiteBalanceMode wb) const
{
    QString name;

    switch (wb) {
    case QCameraImageProcessing::WhiteBalanceAuto:
        name = tr("Auto");
        break;
    case QCameraImageProcessing::WhiteBalanceManual:
        name = tr("Manual");
        break;
    case QCameraImageProcessing::WhiteBalanceSunlight:
        name = tr("Sunlight");
        break;
    case QCameraImageProcessing::WhiteBalanceCloudy:
        name = tr("Cloudy");
        break;
    case QCameraImageProcessing::WhiteBalanceShade:
        name = tr("Shade");
        break;
    case QCameraImageProcessing::WhiteBalanceTungsten:
        name = tr("Tungsten");
        break;
    case QCameraImageProcessing::WhiteBalanceFluorescent:
        name = tr("Fluorescent");
        break;
    case QCameraImageProcessing::WhiteBalanceFlash:
        name = tr("Flash");
        break;
    case QCameraImageProcessing::WhiteBalanceSunset:
        name = tr("Sunset");
        break;
    case QCameraImageProcessing::WhiteBalanceWarmFluorescent:
        name = tr("Warm Fluorescent");
        break;
    default:
        name = tr("Unknown");
        break;
    }
    return name;
}
