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

import QtQuick 2.3

Item {
    id: button
    width: 100
    height: icon.height + caption.height  + icon.anchors.margins * 2 + caption.anchors.bottomMargin
    
    signal clicked;
    
    property alias text: caption.text
    property alias source: icon.source
    property alias font: caption.font
    Image {
        id: icon
        smooth: true
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            margins: 10
  		}
        height: width
        visible: source!=""
        fillMode: Image.PreserveAspectFit
        sourceSize {
            height: height
            width: height
        }
    }
    
    Text {
       id: caption
       anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right
            bottomMargin: 5
       }
       horizontalAlignment: Text.AlignHCenter
       wrapMode: Text.WordWrap
       font.pointSize: 12
       color: mouse.containsMouse ? "red" : "white"      
       Behavior on color { ColorAnimation { duration: 200 } }
    }
    
    MouseArea {
        id: mouse
        anchors.fill: parent
        hoverEnabled: true
        onClicked: button.clicked()
    }
}
