#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "vibro.hpp"

#include "ru_exlmoto_qmldestroytest_NativeHelper.h"

JNIEXPORT void JNICALL Java_ru_exlmoto_qmldestroytest_NativeHelper_invokeVoidMethod
  (JNIEnv *jEnv, jclass jClazz, jint jInt) {
    Q_UNUSED(jEnv);
    Q_UNUSED(jClazz);
    
    qWarning() << "Hello from Java => C++ again! Arg is: " << static_cast<int>(jInt) << " (Function)";
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qmlRegisterType<VibroHelperJNI>("ru.exlmoto", 1, 0, "VibroHelperJNI");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
