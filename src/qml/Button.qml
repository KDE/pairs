import QtQuick 1.1

Rectangle{
    id: button
    width: 100
    height: 200
    color: "transparent"
    signal clicked;
    property alias text: caption.text
    property alias source: icon.source
    Image {
        anchors.top: parent.top
        anchors.horizontalCenter: button.horizontalCenter
        id: icon
        width: 100
        height: 100
    }
    Text {
       id: caption
       width: 100
       anchors.top: icon.bottom
       anchors.horizontalCenter: button.horizontalCenter
       horizontalAlignment: Text.AlignHCenter
       wrapMode: Text.WordWrap
       font.pointSize: 18
    }
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onClicked: button.clicked();
        onEntered: button.state="hovered"
        onExited: button.state="default"
    }
    states: [
        State {
            name: "default"
            PropertyChanges { target: caption; color: "black" }
        },
        State {
            name: "hovered"
            PropertyChanges { target: caption; color: "red" }
        }
    ]
}
