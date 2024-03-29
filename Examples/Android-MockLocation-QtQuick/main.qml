import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.0

import ru.exlmoto 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    HelperJNI {
        id: helperJni
    }

    Column {
        anchors.fill: parent
        anchors.margins: 5
        spacing: 10

//        Button {
//            text: "Vibrate"
//            onClicked: {
//                helperJni.qml_to_cpp_to_jni_to_java__bicycle4ever()
//            }
//        }

        Button {
            text: "Invoke Mock Location Data"
            onClicked: {
                helperJni.cpp_to_java_and_java_to_cpp(0)
            }
        }

        Button {
            text: "Stop Mock Location Service"
            onClicked: {
                helperJni.cpp_to_java_and_java_to_cpp(1)
            }
        }

        Text {
            id: label
            font.family: "Roboto Mono"
            font.pointSize: 12
        }

//        Button {
//            text: "Log Arg"
//            onClicked: {
//                helperJni.readSettings()
//            }
//        }
    }

    Timer {
        id: timer
        interval: 200 // 0.2 sec?
        repeat: true
        triggeredOnStart: false

        onTriggered: {
            label.text = helperJni.getText()
            // console.log("Im Here! " + helperJni.getText());
        }
    }

    Component.onCompleted: {
        timer.start();
    }
}
