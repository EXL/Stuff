#ifndef UTIL_HPP
#define UTIL_HPP

#include <QObject>
#include <QSettings>
#include <QString>

#include <QDebug>

#ifdef Q_OS_ANDROID
#include <QtAndroidExtras/QAndroidJniObject>
#endif

class HelperJNI: public QObject {
    Q_OBJECT

public:
    static int index;
    static double lon;
    static double lat;
    static double alt;

    explicit HelperJNI(QObject* parent = 0): QObject(parent) {
        index = 0;
        lon = 0.0;
        lat = 0.0;
        alt = 0.0;
    }
    Q_INVOKABLE int qml_to_cpp_to_jni_to_java__bicycle4ever() {
        qWarning() << "Vibro: C++";
#ifdef Q_OS_ANDROID
        QAndroidJniObject::callStaticMethod<void>("ru/exlmoto/qmldestroytest/QmlDestroyTest", "vibrate", "(I)V", 30);
#endif
        return 1;
    }
    Q_INVOKABLE int cpp_to_java_and_java_to_cpp(int aZ) {
        qWarning() << "Invoke: C++";
#ifdef Q_OS_ANDROID
        QAndroidJniObject::callStaticMethod<void>("ru/exlmoto/qmldestroytest/QmlDestroyTest", "invoke", "(I)V", aZ);
#endif
        return 1;
    }
    Q_INVOKABLE int readSettings() {
        qWarning() << "!!! READ SETTINGS !!!";
        QSettings settings;
        settings.beginGroup("Eeeeeek");
        qWarning() << "Saved arg is: " << settings.value("Arg").toInt();
        settings.endGroup();
        return 1;
    }
    Q_INVOKABLE QString getText() {
        return /*QString("Index: ") + QString::number(index) +*/
               QString("LON: ") + QString::number(lon) +
               QString(" | LAT: ") + QString::number(lat) +
               QString(" | ALT: ") + QString::number(alt);
    }
};

#endif // UTIL_HPP
