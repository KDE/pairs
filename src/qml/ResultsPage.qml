import QtQuick 1.0

Page {
    Column {
        anchors.fill: parent
        Text {
            font.pixelSize: 70
            anchors.horizontalCenter: parent.horizontalCenter
            
            text: qsTr("Congratulations!")
        }
        
        Repeater {
            model: playersModel
            
            delegate: Row {
                Image { height: 50; width: 50; source: decoration }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 25
                    text: display+". Time: "+time+"\", results: "+found+"/"+missed
                }
            }
        }
        
        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            source: playersModel.iconsDir("gameicons/newgame.png")
            text: qsTr("New Game")
            onClicked: game.state="newgame"
        }
    }
}