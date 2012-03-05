import QtQuick 1.0

FancyBackground
{
    id: game
    Item {
        id: main
        
        anchors {
            right: parent.right
            left: parent.left
            top: parent.top
            bottom: parent.bottom
            leftMargin: 400
            margins: 20
        }
        
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
        
        ResultsPage {
            anchors.fill: parent
            visible: game.state=="congratulations"
        }
    }
    
    Component.onCompleted: game.state="newgame"
    
    Page {
        id: toolbar
        anchors {
            top: parent.top
            right: main.left
            left: game.left
            margins: 20
        }
        height: 100
        
        Row {
            anchors.fill: parent
            id: tools
            spacing: 20
            
            Button {
                source: playersModel.iconsDir("gameicons/quit.png")
                onClicked: Qt.quit()
            }
            
            Button {
                source: playersModel.iconsDir("gameicons/get-hot-new-stuff.png")
                text: qsTr("Get Themes")
                onClicked: fgame.download()
            }
            
            Button {
                source: playersModel.iconsDir("gameicons/newgame.png")
                text: qsTr("New Game")
                visible: game.state=="playing"
                onClicked: {
                    game.state="newgame"
                    fgame.stopGame()
                }
            }
        }
    }
    
    Page {
        id: playersView
        anchors {
            left: parent.left
            right: main.left
            top: toolbar.bottom
            bottom: playersControl.top
            margins: 20
        }
        Text {
            anchors.right: parent.right
            font.pointSize: 14
            text: qsTr("Players")
        }
        
        Flow {
            anchors {
                top: label.bottom
                left: parent.left
                right: parent.right
            }
            spacing: 10
            
            Repeater {
                model: playersModel
                delegate: TogglableButton {
                    text: display+ (game.state=="playing" ? "<br/>"+missed+" "+found+" "+time : "")
                    source: decoration
                    overlaySource: playersModel.iconsDir("gameicons/list-remove-user.png")
                    visible: game.state=="newgame" || selected
                    overlayVisible: game.state=="newgame"
                    opacity: game.state!="playing" || fgame.currentPlayer==index ? 1 : 0.3
                    
                    enabled: selected
                    onClicked: playersModel.toggleSelection(index)
                    onOverlayClicked: {
                        mouseEnabled: false
                        playersModel.removePlayer(index)
                    }
                }
            }
        }
    }
    
    Page {
        id: playersControl
        visible: game.state=='newgame'
        anchors {
            left: parent.left
            right: main.left
            bottom: parent.bottom
            margins: 20
        }
        
        Text {
            id: label
            anchors.right: parent.right
            anchors.top: parent.top
            font.pointSize: 14
            text: qsTr("Join!")
        }
        
        height: 100
        Row {
            id: controls
            anchors.bottom: parent.bottom
            Column {
                Button {
                    id: newUserPicture
                    height: 100
                    width: 100
                    source: playersModel.randomIcon()
//                     asynchronous: true
                    onClicked: source=playersModel.randomIcon()
                }
                TextInput { 
                    id: playerName
                    width: 100 
                    color: "white"
                    text: "Player"
                    focus: true
                    
                    Component.onCompleted: selectAll()
                    onAccepted: addPlayer()
                }
            }
            Button { 
                text: qsTr("Add"); 
                source: playersModel.iconsDir("gameicons/list-add-user.png")
                onClicked: addPlayer()
            }
        }
    }
    
    function addPlayer() {
        playersModel.addPlayer(playerName.text, newUserPicture.source)
        newUserPicture.source=playersModel.randomIcon()
        playerName.selectAll()
    }
    
    states: [
         State { name: "newgame" },
         State { name: "playing" },
         State { name: "congratulations" }
    ]
}