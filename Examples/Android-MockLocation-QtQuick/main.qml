import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.0

import ru.exlmoto 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    
    VibroHelperJNI {
        id: vibro
    }

    Column {
        spacing: 10
        anchors.centerIn: parent
        Button {
            text: "Vibrate"
            onClicked: {
                vibro.qml_to_cpp_to_jni_to_java__bicycle4ever()
            }
        }
        Button {
            text: "Invoke"
            onClicked: {
                vibro.cpp_to_java_and_java_to_cpp()
            }
        }
    }
}
