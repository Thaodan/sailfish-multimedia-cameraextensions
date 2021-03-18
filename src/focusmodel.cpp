/*
  SPDX-FileCopyrightText: Copyright (C) 2021 Jolla Ltd. (bjorn.bidar@jolla.com)
  SPDX-FileCopyrightText: Copyright (C) 2019 Adam Pigg (adam@piggz.co.uk)

  SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "focusmodel.h"

using namespace SFMultimediaCameraExtensions;

class SFMultimediaCameraExtensions::FocusModelPrivate
{
public:
    QMap<int, QString> m_focusModes;
    QCamera *m_camera = nullptr;

};

FocusModel::FocusModel(QObject *parent)
    : QAbstractListModel(parent)
    , d_ptr(new FocusModelPrivate)
{
}
FocusModel::~FocusModel()
{
    Q_D(FocusModel);
    delete d;
}

QHash<int, QByteArray> FocusModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[FocusName] = "name";
    roles[FocusValue] = "value";
    return roles;
}

int FocusModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    Q_D(const FocusModel);
    return d->m_focusModes.count();
}

QVariant FocusModel::data(const QModelIndex &index, int role) const
{
    QVariant v;
    Q_D(const FocusModel);

    if (!index.isValid() || index.row() > rowCount(index) || index.row() < 0) {
        return v;
    }

    if (role == FocusName) {
        v = d->m_focusModes.values().at(index.row());
    } else if (role == FocusValue) {
        v = d->m_focusModes.keys().at(index.row());
    }

    return v;
}

void FocusModel::setCamera(QObject *camera)
{
    QCamera *cam = camera->property("mediaObject").value<QCamera *>();
    Q_D(FocusModel);

    if (d->m_camera != cam) {
        d->m_camera = cam;

        beginResetModel();
        for (int c = (int)QCameraFocus::ManualFocus; c <= (int)QCameraFocus::MacroFocus; c++) {
            if (d->m_camera->focus()->isFocusModeSupported((QCameraFocus::FocusMode)c)
                    && focusName((QCameraFocus::FocusMode)c) != tr("Unknown")) {
                qDebug() << "Found support for" << (QCameraFocus::FocusMode)c;
                d->m_focusModes[(QCameraFocus::FocusMode)c] = focusName((QCameraFocus::FocusMode)c);
            }
        }
        //Add manual mode even if not supported as we simulate it
        if (!d->m_focusModes.contains(QCameraFocus::ManualFocus)) {
            d->m_focusModes[QCameraFocus::ManualFocus] = focusName(QCameraFocus::ManualFocus);
        }
        endResetModel();
        emit rowCountChanged();

        if (d->m_focusModes.size() == 0) {
            qDebug() << "No focus modes found";
        }
    }
}

QString FocusModel::focusName(QCameraFocus::FocusMode focus) const
{
    QString name;
    qDebug() << "Checking focus name: " << focus;

    switch (focus) {
    case QCameraFocus::ManualFocus:
        name = tr("Manual");
        break;
    case QCameraFocus::HyperfocalFocus:
        name = tr("Hyperfocal");
        break;
    case QCameraFocus::InfinityFocus:
        name = tr("Infinity");
        break;
    case QCameraFocus::AutoFocus:
        name = tr("Auto");
        break;
    case QCameraFocus::ContinuousFocus:
        name = tr("Continuous");
        break;
    case QCameraFocus::MacroFocus:
        name = tr("Macro");
        break;
    default:
        name = tr("Unknown");
        break;
    }
    return name;
}
