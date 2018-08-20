#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "util.hpp"

#include <QSettings>

#ifdef Q_OS_ANDROID
#include "ru_exlmoto_qmldestroytest_NativeHelper.h"

void writeSettings(int);

JNIEXPORT void JNICALL Java_ru_exlmoto_qmldestroytest_NativeHelper_invokeVoidMethod
  (JNIEnv *jEnv, jclass jClazz, jint jInt)
{
    Q_UNUSED(jEnv);
    Q_UNUSED(jClazz);

    int arg = static_cast<int>(jInt);

    qWarning() << "Hello from Java => C++ again! Arg is: " << arg << " (Function)";

    qWarning() << "!!! WRITE SETTINGS !!!";
    writeSettings(arg);
}
#endif

void writeSettings(int a_arg)
{
    QSettings settings;
    settings.beginGroup("Eeeeeek");
    settings.setValue("Arg", a_arg);
    settings.endGroup();
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationDomain("ru");
    QCoreApplication::setOrganizationName("exlmoto");
    QCoreApplication::setApplicationName("QmlDestroyTest");

    qmlRegisterType<HelperJNI>("ru.exlmoto", 1, 0, "HelperJNI");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
