import QtQuick 1.0
import '.'

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
        anchors.leftMargin: 400
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
        
        Row{
            Button {
                source: "file://"+playersModel.iconsDir()+"gameicons/get-hot-new-stuff.png"
                text: "Download Themes"
                onClicked: fgame.download()
            }
            Button {
                source: "file://"+playersModel.iconsDir()+"gameicons/newgame.png"
                text: "New Game"
                visible: game.state=="playing"
                onClicked: {
                    playersModel.newGame()
                    game.state="newgame"
                }
            }
            Button {
                source: "file://"+playersModel.iconsDir()+"gameicons/quit.png"
                text: "Quit"
                onClicked: {
                    Qt.quit()
                }
            }
        }
        
        Component {
            id: togglebutton
            Rectangle {
                id: container; 
                width: 100; 
                height: 120
                function toggle() {
                    playersModel.setSelected(index)
                    if(state == "on") 
                    { 
                        state = "off"
                    } 
                    else 
                    { 
                        state = "on" 
                    }
                }
                property bool on: false // variable for outside world
                state: "on"
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
                MouseArea { 
                    id: region; 
                    anchors.fill: parent; 
                    onClicked: {  
                        container.toggle() 
                    }
                }
                // some fanciness
                //color: Behavior { ColorAnimation { duration: 500 } }
                    
                Image {
                    id: image
                    width: 95
                    height: 95
                    anchors.top: parent.top
                    //anchors.centerIn: parent
                    source: decoration
                }
                Text {
                    id: text
                    anchors.top: image.bottom
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 12
                    text: display+" "+missed+" "+found+" "+time
                }
            }
        }
        ListView {
            id: players
            height: 200
            width: parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            Grid {
                columns : 3            
                Repeater {
                    model: playersModel
                    delegate: togglebutton  
                }
            }
        }
        
        Row {
            visible: game.state=='newgame'
            anchors.bottom: parent.bottom
            Column {
                Image {
                    id: newUserPicture
                    height: 100
                    width: 100
                    source: playersModel.randomIcon()
                    asynchronous: true
                    MouseArea {
                        anchors.fill: parent
                        onClicked: parent.source=playersModel.randomIcon()
                    }
                }
                TextInput { 
                    id: playerName; 
                    width: 100 
                    color: "white"
                    text: "Player"
                }
            }
            Button { 
                text: "Add"; 
                source: "file://"+playersModel.iconsDir()+"gameicons/list-add-user.png"
                onClicked: playersModel.addPlayer(playerName.text, newUserPicture.source) 
            }
            Button { 
                text: "Delete Selected"; 
                source: "file://"+playersModel.iconsDir()+"gameicons/list-remove-user.png"
                onClicked: playersModel.removePlayers() 
            }
        }
    }
    
    states: [
         State { name: "newgame" },
         State { name: "playing" },
         State { name: "congratulations" }
     ]
}