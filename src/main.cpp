#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QLocale>
#include <QTranslator>
#include <QQmlContext>
#include <QIcon>
#include "qtollamafrontend.h"

QGuiApplication *appReference;

int main(int argc, char *argv[])
{
    // clean / sharp text
    qputenv("QML_DISABLE_DISTANCEFIELD", "1");
    //QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);

    QGuiApplication app(argc, argv);
    appReference = &app;

    app.setWindowIcon(QIcon(":images/earth.svg"));

    // translation
    /*
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ModxLinguist_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }
    */

    // register qml types
    qmlRegisterType<QtOllamaFrontend>("QtOllamaFrontend.QtOllamaFrontend", 1, 0, "QtOllamaFrontend");

    QQmlApplicationEngine engine;

    QtOllamaFrontend *qtOllamaFrontend = new QtOllamaFrontend();
    engine.rootContext()->setContextProperty("qtOllamaFrontend", qtOllamaFrontend);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("QtOllamaFrontend", "Main");

    return app.exec();
}
