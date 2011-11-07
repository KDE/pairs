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
        anchors.leftMargin: 200
        anchors.margins: 20
        
        Board {
            id: board
            anchors.fill: parent
            
            onIsGameOverChanged: {
                if(isGameOver)
                    game.state="congratulations"
            }
        }
        
        OptionsPage {
            id: options
            anchors.fill: parent
            
            onGameStarted: game.state="playing"
        }
        
        Rectangle {
            id: congratulations
            anchors.fill: parent
            color: "cyan"
            
            Column {
                anchors.horizontalCenter: parent.horizontalCenter
                Text {
                    font.pixelSize: 100
                    anchors.horizontalCenter: parent.horizontalCenter
                    
                    text: "Congratulations!"
                }
                
                Repeater {
                    model: playersModel
                    
                    delegate: Text { font.pixelSize: 25; text: display+". Duration: "+time+", pairs found: "+found+", pairs missed: "+missed }
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
            height: 200
            width: parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            model: playersModel
            
            delegate: Text { text: display+" "+missed+" "+found+" "+time }
        }
    }
    
    states: [
         State {
             name: "newgame"
             PropertyChanges { target: board; visible: false }
             PropertyChanges { target: options; visible: true }
             PropertyChanges { target: congratulations; visible: false }
         },
         State {
             name: "playing"
             PropertyChanges { target: board; visible: true }
             PropertyChanges { target: options; visible: false }
             PropertyChanges { target: congratulations; visible: false }
         },
         State {
             name: "congratulations"
             PropertyChanges { target: board; visible: false }
             PropertyChanges { target: options; visible: false }
             PropertyChanges { target: congratulations; visible: true }
         }
     ]
}