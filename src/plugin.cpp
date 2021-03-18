
#include <QQmlExtensionPlugin>
#include <QGuiApplication>
#include <QQmlEngine>

#include <qqml.h>

//FIXME lib headers

#define QML_URI "org.sailfish.multimedia.cameraextensions"

class CameraPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QML_URI)

public:

    void initializeEngine(QQmlEngine *engine, const char *uri)
    {
        Q_UNUSED(uri)
        Q_UNUSED(engine)
        Q_ASSERT(QLatin1String(uri) == QLatin1String(QML_URI));
    }

    virtual void registerTypes(const char *uri)
    {
        Q_UNUSED(uri)
        Q_ASSERT(QLatin1String(uri) == QLatin1String(QML_URI));

        qmlRegisterType<CaptureModel>(QML_URI, 1, 0, "CaptureModel");
        qmlRegisterType<DeclarativeCameraExtensions>("com.jolla.camera", 1, 0, "CameraExtensions");
        qmlRegisterType<DeclarativeSettings>("com.jolla.camera", 1, 0, "SettingsBase");
        qmlRegisterSingletonType<DeclarativeSettings>("com.jolla.camera", 1, 0, "Settings", DeclarativeSettings::factory);

    }
};

#include "cameraplugin.moc"
