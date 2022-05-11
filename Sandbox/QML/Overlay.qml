import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    color: Qt.rgba(0.0, 0.0, 0.0, 0.5)

    id: window
    visible: true
    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.WA_TranslucentBackground

    Shortcut {
        sequence: "Esc"
        onActivated: window.close()
    }

    DragHandler {
        id: resizeHandler
        onActiveChanged: if (active) {
            const p = resizeHandler.centroid.position
            let e
            if (p.x / width  < 0.10) { e |= Qt.LeftEdge }
            if (p.x / width  > 0.90) { e |= Qt.RightEdge }
            if (p.y / height < 0.10) { e |= Qt.TopEdge }
            if (p.y / height > 0.90) { e |= Qt.BottomEdge }
            if (e) { window.startSystemResize(e) } else { window.startSystemMove() }
        }
    }

    MouseArea {
        anchors.fill: parent
        property real op: 0.5
        onWheel: {
            if (wheel.angleDelta.y > 0 && op < 1.0)
                op += 0.01
            else if (wheel.angleDelta.y < 0 && op > 0.0)
                op -= 0.01
            window.color = Qt.rgba(0.0, 0.0, 0.0, op)
        }
    }
}
