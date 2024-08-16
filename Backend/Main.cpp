#include "Backend/SceneVtkItem.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickVTKRenderWindow.h>
#include <QQuickWindow>

#include <QVTKRenderWindowAdapter.h>

extern "C" {
    _declspec(dllexport) int NvOptimusEnablement = 1;
    _declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

int main(int argc, char *argv[])
{
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGLRhi);
    QSurfaceFormat::setDefaultFormat(QVTKRenderWindowAdapter::defaultFormat());

    QGuiApplication app(argc, argv);

    qmlRegisterType<SceneVtkItem>("Vtk", 1, 0, "SceneVtkItem");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/Gui/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
