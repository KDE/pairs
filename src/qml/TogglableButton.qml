import QtQuick 1.0

Rectangle
{
    id: container
    width: 100; 
    height: 120
    
    property bool enabled: true
    property alias text: button.text
    property alias source: button.source
    property alias overlaySource: button.overlaySource
    signal overlayClicked
    signal clicked
    
    state: enabled ? "off" : "on"
    states: [
        State {
            name: "on";
            PropertyChanges{ target: container; color: "blue" }
        },
        State {
            name: "off";
            PropertyChanges{ target: container; color: "lightblue" }
        }
    ]
    
    Button {
        id: button
        
        onClicked: container.clicked()
        onOverlayClicked: container.overlayClicked()
    }
}