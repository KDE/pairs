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

Flickable {
    id: gameSettings
    property string gameType: 'image'
    
    signal gameStarted;
    contentHeight: games.height
    Column {
        id: games
        width: parent.width
        spacing: 20
        Page {
            height: gameTypes.height
            width: parent.width
            Flow {
                id: gameTypes
                spacing: 20
                anchors.margins: 10
                width: parent.width
                property real buttonWidth: 107
                TogglableButton {
                    width: parent.buttonWidth
                    source: playersModel.iconsDir("gameicons/pairs.svg")
                    text: i18n("Pairs")
                    onClicked: gameType = 'image'
                    enabled: gameType == 'image'
                }
                TogglableButton {
                    width: parent.buttonWidth
                    source: playersModel.iconsDir("gameicons/relations.svg")
                    text: i18n("Relations")
                    onClicked: gameType = 'image2'
                    enabled: gameType == 'image2'
                }
                TogglableButton {
                    width: parent.buttonWidth
                    source: playersModel.iconsDir("gameicons/logic.svg")
                    text: i18n("Logic")
                    onClicked: gameType = 'logic'
                    enabled: gameType == 'logic'
                }
                TogglableButton {
                    width: parent.buttonWidth
                    source: playersModel.iconsDir("gameicons/sound.svg")
                    text: i18n("Sound")
                    onClicked: gameType = 'sound'
                    enabled: gameType == 'sound'
                }
                TogglableButton {
                    width: parent.buttonWidth
                    source: playersModel.iconsDir("gameicons/soundLogic.svg")
                    text: i18n("SoundLogic")
                    onClicked: gameType = 'soundlogic'
                    enabled: gameType == 'soundlogic'
                }
                TogglableButton {
                    width: parent.buttonWidth
                    source: playersModel.iconsDir("gameicons/words.svg")
                    text: i18n("Words")
                    onClicked: gameType = 'word'
                    enabled: gameType == 'word'
                }
            }
        }
        
        Page {
            width: parent.width
            height: themesView.height
            Flow {
                id: themesView
                width: parent.width
                spacing: 20
                anchors.margins: 10
                
                Repeater {
                    model: themesModel
                    
                    delegate: Button {
	                	width: Math.max((themesView.width - 120) / 6, 100)
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
                                    playersControl.addPlayer()
                            }
                            
                            gameStarted()
                            fgame.newGame(index, gameType)
                        }
                    }
                }
            }
        }
    }
}
