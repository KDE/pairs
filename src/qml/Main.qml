/*
 *  Copyright (C) <2011>       <Aleix Pol>           <aleixpol@kde.org>
 *  Copyright (C) <2011>       <Marco Calignano>     <marco.calignano@googlemail.com>
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation; either version 2 of
 *  the License or (at your option) version 3 or any later version
 *  accepted by the membership of KDE e.V. (or its successor approved
 *  by the membership of KDE e.V.), which shall act as a proxy 
 *  defined in Section 14 of version 3 of the license.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 1.0

FancyBackground
{
    id: game
    Item {
        id: main
        
        anchors {
            fill: parent
            leftMargin: Math.min(game.width/3, 320)
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
        InfoPage {
            anchors.fill: parent
            visible: game.state=="info"
            MouseArea {
                anchors.fill: parent
                onClicked: game.state="newgame"
            }
            
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
        height: 130
        
        Row {
            anchors.fill: parent
            id: tools
            property real buttonWidth: Math.min(tools.width/3, 100)
            
            Button {
                width: tools.buttonWidth
                source: playersModel.iconsDir("gameicons/exit.svg")
                text: i18n("Quit")
                onClicked: Qt.quit()
            }
            
            Button {
                width: tools.buttonWidth
                source: playersModel.iconsDir("gameicons/getThemes.svg")
                text: i18n("Get Themes")
                onClicked: fgame.download()
                visible: game.state=="newgame"
            }
            
            Button {
                width: tools.buttonWidth
                source: playersModel.iconsDir("gameicons/info.svg")
                text: i18n("Info")
                visible: game.state=="newgame"
                onClicked: {
                    game.state="info"
                }
            }
            Button {
                width: tools.buttonWidth
                source: playersModel.iconsDir("gameicons/newGame.svg")
                text: i18n("New Game")
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
        clip: true
        anchors {
            left: parent.left
            right: main.left
            top: toolbar.bottom
            bottom: playersControl.top
            leftMargin: 20
            rightMargin: 20
        }
        Flickable {
            anchors.fill: parent
            contentHeight: playersLabel.height+playersFlow.height
            Text {
                id: playersLabel
                anchors {
                    right: parent.right
                    rightMargin: 5
                }
                font.pointSize: 14
                color : "white"
                text: i18n("Players")
            }
            
            Flow {
                id: playersFlow
                anchors {
                    top: playersLabel.bottom
                    left: parent.left
                    right: parent.right
                    margins: 5
                }
                spacing: 10
                
                Repeater {
                    model: playersModel
                    delegate: TogglableButton {
                        text: game.state!="playing" ? display : i18nc("name. found/tries, time seconds", "%1<br/>%2/%3, %4s", display, found, missed+found, time)
                        source: decoration
                        overlaySource: playersModel.iconsDir("gameicons/removeUser.svg")
                        visible: game.state=="newgame" || selected
                        overlayVisible: game.state=="newgame"
                        opacity: game.state!="playing" || fgame.currentPlayer==index ? 1 : 0.3
                        width: Math.min(100, parent.width)
                        
                        enabled: selected
                        onClicked: if(game.state=="newgame") playersModel.toggleSelection(index)
                        onOverlayClicked: playersModel.removePlayer(index)
                    }
                }
            }
        }
    }
    
    Page {
        id: playersControl
        visible: game.state=='newgame'
        height: visible ? addPlayer.height + label.height : 0
        anchors {
            left: parent.left
            right: main.left
            bottom: parent.bottom
            margins: 20
        }
        
        Text {
            id: label
            anchors {
                right: parent.right
                top: parent.top
                rightMargin: 5
            }
            font.pointSize: 14
            color: "white"
            text: i18n("Join!")
        }
        
        Item {
            id: controls
            anchors {
                fill: parent
                topMargin: label.height
            }
            Image {
                id: newUserPicture
                smooth: true
                anchors {
                    left: parent.left
                    top: parent.top
                    bottom: parent.bottom
                    right: playerNameControls.left
                    margins: 3
                }
                fillMode: Image.PreserveAspectFit
                source: playersModel.randomIcon()
                MouseArea {
                    anchors.fill: parent
                    onClicked: newUserPicture.source=playersModel.randomIcon()
                }
            }
            
            Column {
                id: playerNameControls
                anchors.verticalCenterOffset: -10
                anchors.verticalCenter: newUserPicture.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                Text {
                    color: "white" 
                    text: i18n("Player Name:") 
                }
                
                TextInput { 
                    id: playerName
                    width: 100 
                    color: "white"
                    text: i18n("Player")
                    focus: true
                    
                    Component.onCompleted: selectAll()
                    onAccepted: addPlayer()
                }
            }
        }
        
        Button {
        	id: addPlayer
            anchors {
                right: parent.right
                bottom: parent.bottom
                bottomMargin: -10
            }
            width: 100
            text: i18n("Add"); 
            source: playersModel.iconsDir("gameicons/addUser.svg")
            onClicked: addPlayer()
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
         State { name: "congratulations" },
         State { name: "info" }
    ]
}
