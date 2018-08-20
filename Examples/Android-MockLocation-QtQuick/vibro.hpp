#ifndef VIBRO_HPP
#define VIBRO_HPP

#include <QObject>
#include <QDebug>

#ifdef Q_OS_ANDROID
#include <QtAndroidExtras/QAndroidJniObject>
#endif

class VibroHelperJNI: public QObject {
    Q_OBJECT
    
public:
    explicit VibroHelperJNI(QObject* parent = 0): QObject(parent) { }
    Q_INVOKABLE int qml_to_cpp_to_jni_to_java__bicycle4ever() {
        qWarning() << "Vibro: C++";
#ifdef Q_OS_ANDROID
        QAndroidJniObject::callStaticMethod<void>("ru/exlmoto/qmldestroytest/QmlDestroyTest", "vibrate", "(I)V", 30);
#endif
        return 1;
    }
    Q_INVOKABLE int cpp_to_java_and_java_to_cpp() {
        qWarning() << "Invoke: C++";
#ifdef Q_OS_ANDROID
        QAndroidJniObject::callStaticMethod<void>("ru/exlmoto/qmldestroytest/QmlDestroyTest", "invoke", "(I)V", 30);
#endif
        return 1;
    }
};

#endif // VIBRO_HPP
