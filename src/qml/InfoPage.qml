import QtQuick 1.0

Page {
    Column {
        anchors.fill: parent
        Text {
            font.pixelSize: 20
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("pairs v 0.2.0")
        }
        Text {
            font.pixelSize: 20
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Aleix Pol Gonzalez - Initial implementation and maintainer - aleixpol@kde.org")
        }
        Text {
            font.pixelSize: 20
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Marco Calignano - Theme support enhancement and general feature development - marco.calignano@googlemail.com")
        }
        Text {
            font.pixelSize: 20
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Albert Astals Cid - Initial project setup and ideas - aacid@kde.org")
        }
    }
}