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

import QtQuick 1.1

Rectangle{
    id: button
    width: 100
    height: 100
    color: "transparent"
    
    signal clicked;
    signal overlayClicked;
    
    property alias text: caption.text
    property alias source: icon.source
    property alias overlaySource: overlay.source
    property alias hoverEnabled: mouse.hoverEnabled
    property alias mouseEnabled: mouse.enabled
    property alias font: caption.font
    property bool overlayVisible: true
    Image {
        id: icon
        anchors.top: parent.top
        anchors.horizontalCenter: button.horizontalCenter
        fillMode: Image.PreserveAspectFit
        
        width: parent.width*2/3
        height: parent.height*2/3
    }
    
    Text {
       id: caption
       width: 100
       color: "white"
       anchors.top: icon.bottom
       anchors.horizontalCenter: button.horizontalCenter
       horizontalAlignment: Text.AlignHCenter
       wrapMode: Text.WordWrap
       font.pointSize: 14
    }
    
    MouseArea {
        id: mouse
        anchors.fill: parent
        hoverEnabled: true
        onClicked: button.clicked()
        onEntered: button.state="hovered"
        onExited: button.state="default"
    }
    
    Image { 
        id: overlay
        
        visible: mouse.containsMouse && overlayVisible
        width: parent.width/3
        height: parent.height/3
        anchors.top: parent.top
        anchors.right: parent.right
        
        MouseArea {
            anchors.fill: parent
            onClicked: button.overlayClicked()
        }
    }
    
    states: [
        State {
            name: "default"
            PropertyChanges { target: caption; color: "white" }
        },
        State {
            name: "hovered"
            PropertyChanges { target: caption; color: "red" }
        }
    ]
}
