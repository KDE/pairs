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
                anchors.margins: 20
                spacing: 20
                Image { height: 200; width: 200; source: decoration }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 25
                    text: qsTr(display+". Time: "+time+"\", results: "+found+"/"+(found+missed))
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