#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "FileModifier.h"

int main(int argc, char* argv[]) {
#if defined(Q_OS_WIN) && QT_VERSION_CHECK(5, 6, 0) <= QT_VERSION && QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qt/qml/qttest/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    FileModifier modifier;
    engine.rootContext()->setContextProperty("modifier", &modifier);

    return app.exec();
}