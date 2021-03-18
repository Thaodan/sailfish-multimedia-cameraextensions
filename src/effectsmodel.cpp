/*
  SPDX-FileCopyrightText: Copyright (C) 2021 Jolla Ltd. (bjorn.bidar@jolla.com)
  SPDX-FileCopyrightText: Copyright (C) 2019 Adam Pigg (adam@piggz.co.uk)

  SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "effectsmodel.h"

using namespace SFMultimediaCameraExtensions;

class SFMultimediaCameraExtensions::EffectsModelPrivate
{
public:
    QMap<QCameraImageProcessing::ColorFilter, QString> m_effects;
    QCamera *m_camera = nullptr;
};

EffectsModel::EffectsModel(QObject *parent)
    : QAbstractListModel(parent)
    , d_ptr(new EffectsModelPrivate)
{
}

EffectsModel::~EffectsModel()
{
    Q_D(EffectsModel);
    delete d;
}


QHash<int, QByteArray> EffectsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[EffectName] = "name";
    roles[EffectValue] = "value";
    return roles;
}

int EffectsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    Q_D(const EffectsModel);
    return d->m_effects.count();
}

QVariant EffectsModel::data(const QModelIndex &index, int role) const
{
    QVariant v;
    Q_D(const EffectsModel);

    if (!index.isValid() || index.row() > rowCount(index) || index.row() < 0) {
        return v;
    }

    if (role == EffectName) {
        v = d->m_effects.values().at(index.row());
    } else if (role == EffectValue) {
        v = d->m_effects.keys().at(index.row());
    }

    return v;
}

void EffectsModel::setCamera(QObject *camera)
{
    Q_D(EffectsModel);

    QCamera *cam = camera->property("mediaObject").value<QCamera *>();
    if (d->m_camera != cam) {
        d->m_camera = cam;

        beginResetModel();
        for (int c = (int)QCameraImageProcessing::ColorFilterNone;
                c <= (int)QCameraImageProcessing::ColorFilterNeon; c++) {
            if (d->m_camera->imageProcessing()->isColorFilterSupported((QCameraImageProcessing::ColorFilter)c)) {
                qDebug() << "Found support for" << (QCameraImageProcessing::ColorFilter)c;
                d->m_effects[(QCameraImageProcessing::ColorFilter)c] = effectName((QCameraImageProcessing::ColorFilter)c);
            }
        }
        endResetModel();
        emit rowCountChanged();

        if (d->m_effects.size() == 0) {
            qDebug() << "No effect modes found";
        }
    }
}

QString EffectsModel::effectName(QCameraImageProcessing::ColorFilter c) const
{
    QString name;

    switch (c) {
    case QCameraImageProcessing::ColorFilterNone:
        name = tr("None");
        break;
    case QCameraImageProcessing::ColorFilterAqua:
        name = tr("Aqua");
        break;
    case QCameraImageProcessing::ColorFilterBlackboard:
        name = tr("Blackboard");
        break;
    case QCameraImageProcessing::ColorFilterGrayscale:
        name = tr("Grayscale");
        break;
    case QCameraImageProcessing::ColorFilterNegative:
        name = tr("Negative");
        break;
    case QCameraImageProcessing::ColorFilterPosterize:
        name = tr("Posterize");
        break;
    case QCameraImageProcessing::ColorFilterSepia:
        name = tr("Sepia");
        break;
    case QCameraImageProcessing::ColorFilterSolarize:
        name = tr("Solarize");
        break;
    case QCameraImageProcessing::ColorFilterWhiteboard:
        name = tr("Whiteboard");
        break;
    case QCameraImageProcessing::ColorFilterEmboss:
        name = tr("Emboss");
        break;
    case QCameraImageProcessing::ColorFilterSketch:
        name = tr("Sketch");
        break;
    case QCameraImageProcessing::ColorFilterNeon:
        name = tr("Neon");
        break;
    default:
        name = "Unknown";
        break;
    }

    return name;
}
