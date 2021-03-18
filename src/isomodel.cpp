/*
  SPDX-FileCopyrightText: Copyright (C) 2021 Jolla Ltd. (bjorn.bidar@jolla.com)
  SPDX-FileCopyrightText: Copyright (C) 2019 Adam Pigg (adam@piggz.co.uk)

  SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "isomodel.h"

using namespace SFMultimediaCameraExtensions;

class SFMultimediaCameraExtensions::IsoModelPrivate
{
public:
    QMap<int, QString> m_isoModes;
    QCamera *m_camera = nullptr;
};

IsoModel::IsoModel(QObject *parent)
    : QAbstractListModel(parent)
    , d_ptr(new IsoModelPrivate)
{
}

IsoModel::~IsoModel()
{
    Q_D(IsoModel);
    delete d;
}

QHash<int, QByteArray> IsoModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IsoName] = "name";
    roles[IsoValue] = "value";
    return roles;
}

int IsoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    Q_D(const IsoModel);

    return d->m_isoModes.count();
}

QVariant IsoModel::data(const QModelIndex &index, int role) const
{
    QVariant v;
    Q_D(const IsoModel);

    if (!index.isValid() || index.row() > rowCount(index) || index.row() < 0) {
        return v;
    }

    if (role == IsoName) {
        v = d->m_isoModes.values().at(index.row());
    } else if (role == IsoValue) {
        v = d->m_isoModes.keys().at(index.row());
    }

    return v;
}

void IsoModel::setCamera(QObject *camera)
{
    QCamera *cam = camera->property("mediaObject").value<QCamera *>();
    Q_D(IsoModel);

    if (d->m_camera != cam) {
        d->m_camera = cam;

        beginResetModel();

        QList<int> supportedIsoRange = d->m_camera->exposure()->supportedIsoSensitivities();

        for (int i = 0; i < supportedIsoRange.count() ; i++) {
            d->m_isoModes[supportedIsoRange[i]] = isoName(supportedIsoRange[i]);
            qDebug() << "Found support for" << isoName(supportedIsoRange[i]);
        }
        endResetModel();
        emit rowCountChanged();

        if (d->m_isoModes.size() == 0) {
            qDebug() << "No ISO modes found";
        }
    }
}

QString IsoModel::isoName(int iso) const
{
    QString name;

    if (iso == 0) {
        name = tr("Auto ISO");
    } else if (iso == 1) {
        name = "ISO_HJR";
    } else {
        name = QString("ISO_%1").arg(iso);
    }
    return name;
}
