import QtQuick 1.0

Page {
    Column {
        anchors.fill: parent
        Text {
            font.pixelSize: 20
            anchors.horizontalCenter: parent.horizontalCenter
            text: i18n("pairs v 0.2.0")
        }
        Text {
            font.pixelSize: 20
            anchors.horizontalCenter: parent.horizontalCenter
            text: i18n("Aleix Pol Gonzalez - Initial implementation and maintainer - aleixpol@kde.org")
        }
        Text {
            font.pixelSize: 20
            anchors.horizontalCenter: parent.horizontalCenter
            text: i18n("Marco Calignano - Theme support enhancement and general feature development - marco.calignano@googlemail.com")
        }
        Text {
            font.pixelSize: 20
            anchors.horizontalCenter: parent.horizontalCenter
            text: i18n("Albert Astals Cid - Initial project setup and ideas - aacid@kde.org")
        }
    }
}