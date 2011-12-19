import QtQuick 1.1

Rectangle{
    id: button
    width: 100
    height: 100
    color: "transparent"
    
    signal clicked;
    signal overlayClicked;
    
    property alias text: caption.text
    property alias source: icon.source
    property alias overlaySource: overlay.source
    property alias hoverEnabled: mouse.hoverEnabled
    property alias font: caption.font
    property bool overlayVisible: true
    Image {
        id: icon
        anchors.top: parent.top
        anchors.horizontalCenter: button.horizontalCenter
        fillMode: Image.PreserveAspectFit
        
        width: parent.width*2/3
        height: parent.height*2/3
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
        id: mouse
        anchors.fill: parent
        hoverEnabled: true
        onClicked: button.clicked()
        onEntered: button.state="hovered"
        onExited: button.state="default"
    }
    
    Image { 
        id: overlay
        
        visible: mouse.containsMouse && overlayVisible
        width: parent.width/3
        height: parent.height/3
        anchors.top: parent.top
        anchors.right: parent.right
        
        MouseArea {
            anchors.fill: parent
            onClicked: button.overlayClicked()
        }
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
