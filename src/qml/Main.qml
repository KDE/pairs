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
        
        Button {
            source: "file:///usr/share/icons/oxygen/128x128/apps/kmail2.png"
            text: "Download Themes"
            onClicked: fgame.download()
        }
        
        Component {
            id: togglebutton
            //width: 200; height: 200
            Rectangle {
                id: container; 
                width: 100; 
                height: 120
                function toggle() {
                    if(state == "on") { state = "off" } else { state = "on" }
                }
                property bool on: false // variable for outside world
                state: "on"
                states: [
                    State {
                        name: "on";
                        PropertyChanges{ target: container; color: "blue" }
                        PropertyChanges{ on: true } // change on variable
                    },
                    State {
                        name: "off";
                        PropertyChanges{ target: container; color: "lightblue" }
                        PropertyChanges{ on: false } // change on variable
                    }
                ]
                MouseArea { id: region; anchors.fill: parent; onClicked: container.toggle() }
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
                  //  anchors.centerIn: parent
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
            Image {
                id: newUserPicture
                height: 20
                width: 20
                source: playersModel.randomIcon()
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