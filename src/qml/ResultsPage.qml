/*
 *  Copyright (C) <2011>       <Aleix Pol>           <aleixpol@kde.org>
 *  Copyright (C) <2012>       <Marco Calignano>     <marco.calignano@googlemail.com>
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
    Column {
        anchors.fill: parent
        Text {
            font.pixelSize: 70
            anchors.horizontalCenter: parent.horizontalCenter
            color: "white"
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
                    color: "white"
                    text: i18n("%1. Time: %2. Results: %3", display, time, found)
                }
            }
        }
        
        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            source: playersModel.iconsDir("gameicons/newGame.svg")
            text: i18n("New Game")
            onClicked: game.state="newgame"
        }
    }
}
