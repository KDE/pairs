import QtQuick 1.0

Rectangle
{
    id: container
    width: 100; 
    height: 120
    
    gradient: Gradient {
        GradientStop { id: from; position: 0 }
        GradientStop { position: 1; color: "transparent" }
    }
    
    property bool enabled: true
    property alias text: button.text
    property alias source: button.source
    property alias overlaySource: button.overlaySource
    signal overlayClicked
    signal clicked
    
    state: enabled ? "on" : "off"
    states: [
        State {
            name: "on";
            PropertyChanges{ target: from; color: "#77FFFFFF" }
        },
        State {
            name: "off";
            PropertyChanges{ target: from; color: "transparent" }
        }
    ]
    
    Button {
        id: button
        
        onClicked: container.clicked()
        onOverlayClicked: container.overlayClicked()
    }
}