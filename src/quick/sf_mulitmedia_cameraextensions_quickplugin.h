/*
  SPDX-FileCopyrightText: Copyright (C) Jolla Ltd. (bjorn.bidar@jolla.com)

  SPDX-License-Identifier: LGPL-2.1-or-later

  -*- mode: c++ -*-
*/

#ifndef SFMULTIMEDIACAMERAEXTENSIONSPLUGIN_H
#define SFMULTIMEDIACAMERAEXTENSIONSPLUGIN_H

#include <QQmlExtensionPlugin>

class SFMultimediaCameraExtensionsPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.sailfish.multimedia.cameraextensions")

public:
    void registerTypes(const char *uri) override;
};

#endif
