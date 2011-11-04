import QtQuick 1.1

ListView
{
    id: root;
    
    highlightFollowsCurrentItem: true
    highlightRangeMode: ListView.ApplyRange
    highlight: Rectangle {
        gradient: Gradient {
            GradientStop { position: 0; color: "lightsteelblue" }
            GradientStop { position: 1; color: "transparent" }
        }
        
        radius: 5
    }
    
    MouseArea {
        anchors.fill: parent
        
        onClicked: {
            var idx=root.indexAt(mouse.x, mouse.y)
            root.currentIndex=idx
        }
    }
}