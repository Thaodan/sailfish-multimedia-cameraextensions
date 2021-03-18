/*
  SPDX-FileCopyrightText: Copyright (C) Jolla Ltd. (bjorn.bidar@jolla.com)

  SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "sf_mulitmedia_cameraextensions_quickplugin.h"

#include "effectsmodel.h"
#include "exposuremodel.h"
#include "flashmodel.h"
#include "focusmodel.h"
#include "isomodel.h"
#include "resolutionmodel.h"
#include "whitebalancemodel.h"

#define QML_URI "org.sailfish.multimedia.cameraextensions"

#include <qqml.h>

using namespace SFMultimediaCameraExtensions;

void SFMultimediaCameraExtensionsPlugin::registerTypes(const char *uri)
{
    Q_UNUSED(uri);
    Q_ASSERT(QLatin1String(uri) == QLatin1String(QML_URI));

    qmlRegisterType<ExposureModel>(QML_URI, 1, 0,"ExposureModel");
    qmlRegisterType<FlashModel>(QML_URI, 1, 0,"FlashModel");
    qmlRegisterType<FocusModel>(QML_URI, 1, 0,"FocusModel");
    qmlRegisterType<IsoModel>(QML_URI, 1, 0,"IsoModel");
    qmlRegisterType<ResolutionModel>(QML_URI, 1, 0,"ResolutionModel");
    qmlRegisterType<WhiteBalanceModel>(QML_URI, 1, 0,"WhiteBalanceModel");
}
