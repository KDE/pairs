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
        InfoPage {
            anchors.fill: parent
            visible: game.state=="info"
            MouseArea {
                id: mouse
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
        height: 100
        
        Row {
            anchors.fill: parent
            id: tools
            spacing: 20
            
            Button {
                source: playersModel.iconsDir("gameicons/exit.svg")
                onClicked: Qt.quit()
            }
            
            Button {
                source: playersModel.iconsDir("gameicons/getThemes.svg")
                text: i18n("Get Themes")
                onClicked: fgame.download()
            }
            
            Button {
                source: playersModel.iconsDir("gameicons/info.svg")
                text: i18n("Info")
                visible: game.state=="newgame"
                onClicked: {
                    game.state="info"
                }
            }
            Button {
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
        anchors {
            left: parent.left
            right: main.left
            top: toolbar.bottom
            bottom: playersControl.top
            margins: 20
        }
        Text {
            id: playersLabel
            anchors.right: parent.right
            font.pointSize: 14
            color : "white"
            text: i18n("Players")
        }
        
        Flow {
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
            color: "white"
            text: i18n("Join!")
        }
        
        height: 100
        Row {
            id: controls
            anchors.top: label.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            Button {
                id: newUserPicture
                anchors.verticalCenter: parent.verticalCenter
                source: playersModel.randomIcon()
                onClicked: source=playersModel.randomIcon()
            }
            
            Column {
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
            Button { 
                text: i18n("Add"); 
                source: playersModel.iconsDir("gameicons/addUser.svg")
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
         State { name: "congratulations" },
         State { name: "info" }
    ]
}