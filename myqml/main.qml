import QtQuick 2.0
import QtQuick.Window 2.0

Window {
    visible: true
    MyHelloWorld {
        anchors.fill: parent
        mArea.onClicked: {
            Qt.quit()
        }
    }
}
