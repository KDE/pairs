import QtQuick 1.0

Page {
    Column {
        anchors.fill: parent
        Text {
            font.pixelSize: 70
            anchors.horizontalCenter: parent.horizontalCenter
            
            text: i18n("Congratulations!")
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
                    text: i18n(display+". Time: "+time+"\", results: "+found+"/"+(found+missed))
                }
            }
        }
        
        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            source: playersModel.iconsDir("gameicons/newgame.png")
            text: i18n("New Game")
            onClicked: game.state="newgame"
        }
    }
}