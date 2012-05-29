/*
 *  Copyright (C) <2011>       <Aleix Pol>           <aleixpol@kde.org>
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

Item
{
    id: container
    width: 100
    height: 120
    property bool enabled: true
    property alias text: button.text
    property alias source: button.source
    property alias overlaySource: overlay.source
    property bool overlayVisible: true
    
    signal overlayClicked
    signal clicked
    
    Rectangle {
        radius: 20
        smooth: true
        anchors.fill: parent
        opacity: container.enabled ? 0.7 : 0
        Behavior on opacity { NumberAnimation { duration: 200 } }
        gradient: Gradient {
            GradientStop { position: 0; color: "white" }
            GradientStop { position: 1; color: "transparent" }
        }
    }
    
    MouseArea {
        id: mouse
        anchors.fill: parent
        hoverEnabled: true
        onClicked: button.clicked()
        onEntered: button.state="hovered"
        onExited: button.state="default"
        
        Button {
            id: button
            anchors.fill: parent
            anchors.verticalCenterOffset: -10
            
            onClicked: container.clicked()
            onOverlayClicked: container.overlayClicked()
        }
        
        Image { 
            id: overlay
            
            opacity: !container.enabled && overlayVisible ? 1 : 0
            width: parent.width/3
            height: parent.height/3
            anchors.top: parent.top
            anchors.right: parent.right
            Behavior on opacity { NumberAnimation { duration: 200; easing.type: Easing.InQuad } }
            
            MouseArea {
                anchors.fill: parent
                onClicked: button.overlayClicked()
            }
        }
    }
}