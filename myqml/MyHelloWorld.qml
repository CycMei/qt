import QtQuick 2.0

Rectangle {
    width: 500
    height: 62
    property alias mArea: mouseArea
    Text {
        id: name
        text: qsTr("hello world")
        anchors.centerIn: parent
    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }
}
