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

Page {
    id: gameSettings
    property string gameType: 'image'
    
    signal gameStarted;
    
    Column {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 50
        Flow {
            width: parent.width
            spacing: 20
            TogglableButton {
                source: playersModel.iconsDir("gameicons/pairs.png")
                text: i18n("Pairs")
                onClicked: gameType = 'image'
                enabled: gameType == 'image'
            }
            TogglableButton {
                source: playersModel.iconsDir("gameicons/pairs2.png")
                text: i18n("Relations")
                onClicked: gameType = 'image2'
                enabled: gameType == 'image2'
            }
            TogglableButton {
                source: playersModel.iconsDir("gameicons/logic.png")
                text: i18n("Logic")
                onClicked: gameType = 'logic'
                enabled: gameType == 'logic'
            }
            TogglableButton {
                source: playersModel.iconsDir("gameicons/sound.png")
                text: i18n("Sound")
                onClicked: gameType = 'sound'
                enabled: gameType == 'sound'
            }
            TogglableButton {
                source: playersModel.iconsDir("gameicons/sound.png")
                text: i18n("SoundLogic")
                onClicked: gameType = 'soundlogic'
                enabled: gameType == 'soundlogic'
            }
            TogglableButton {
                source: playersModel.iconsDir("gameicons/words.png")
                text: i18n("Words")
                onClicked: gameType = 'word'
                enabled: gameType == 'word'
            }
        }
        
        Flow {
            id: themesView
            width: parent.width
            spacing: 20
            
            Repeater {
                model: themesModel
                
                delegate: Button {
                    visible: themesModel.isPertinent(index, gameType, fgame.language())
                    source: "image://theme/"+display+"/"+decoration
                    text: display
                    font.pointSize: 12
                    
                    onClicked: {
                        if(!playersModel.isAnySelected()) {
                            //if there are no selected players, select the first one
                            //if there's none, just create one
                            if(playersModel.count>0)
                                playersModel.toggleSelection(0)
                            else
                                addPlayer()
                        }
                        
                        gameStarted()
                        fgame.newGame(index, gameType)
                    }
                }
            }
        }
    }
}