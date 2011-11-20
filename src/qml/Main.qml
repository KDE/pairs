import QtQuick 1.0


Rectangle
{
    id: game
    color: 'blue'
    Item {
        id: main
        
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: 250
        anchors.margins: 20
        
        Board {
            id: board
            anchors.fill: parent
            visible: game.state=="playing"
            
            onIsGameOverChanged: {
                if(isGameOver)
                    game.state="congratulations"
            }
        }
        
        OptionsPage {
            id: options
            anchors.fill: parent
            visible: game.state=="newgame"
            
            onGameStarted: game.state="playing"
        }
        
        Rectangle {
            id: congratulations
            anchors.fill: parent
            color: "cyan"
            visible: game.state=="congratulations"
            
            Column {
                anchors.horizontalCenter: parent.horizontalCenter
                Text {
                    font.pixelSize: 100
                    anchors.horizontalCenter: parent.horizontalCenter
                    
                    text: "Congratulations!"
                }
                
                Repeater {
                    model: playersModel
                    
                    delegate: Row {
                        Image { height: 20; width: 20; source: decoration }
                        Text { font.pixelSize: 25; text: display+". Duration: "+time+", pairs found: "+found+", pairs missed: "+missed }
                    }
                }
                
                Button {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Start New Game"
                    
                    onClicked: game.state="newgame"
                }
            }
        }
    }
    
    Component.onCompleted: game.state="newgame"
    
    Column {
        anchors.margins:20
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: main.left
        anchors.left: parent.left
        
        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            
            text: "New Game"
            onClicked: game.state="newgame"
        }
        
        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            
            text: "Play"
            onClicked: game.state="playing"
        }
        
        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            
            text: "Congratulate"
            onClicked: game.state="congratulations"
        }
        
        ListView {
            id: players
            height: 200
            width: parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            Grid {
                columns : 2            
                Repeater {
                    model: playersModel
                    delegate: Column { 
                        Image {
                            height: 100; width: 100
                            source: decoration
                        }
                        Text { text: display+" "+missed+" "+found+" "+time }
                        Button {
                            text: 'Remove'
                            visible: game.state=='newgame'
                            onClicked: playersModel.removePlayer(display);
                        }
                    }
                }
            }
        }
        
        Row {
            visible: game.state=='newgame'
            anchors.bottom: parent.bottom
            Image {
                id: newUserPicture
                height: 20
                width: 20
                source: themesModel.randomThemesImage()
                asynchronous: true
                
                MouseArea {
                    anchors.fill: parent
                    onClicked: parent.source=themesModel.randomThemesImage()
                }
            }
            TextInput { id: playerName; width: 100 }
            Button { text: "Add"; onClicked: playersModel.addPlayer(playerName.text, newUserPicture.source) }
        }
    }
    
    states: [
         State { name: "newgame" },
         State { name: "playing" },
         State { name: "congratulations" }
     ]
}