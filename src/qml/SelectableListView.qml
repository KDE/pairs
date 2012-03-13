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

import QtQuick 1.1

ListView
{
    id: root;
    
    highlightFollowsCurrentItem: true
    highlightRangeMode: ListView.ApplyRange
    highlight: Rectangle {
        gradient: Gradient {
            GradientStop { position: 0; color: "lightsteelblue" }
            GradientStop { position: 1; color: "transparent" }
        }
        
        radius: 5
    }
    
    MouseArea {
        anchors.fill: parent
        
        onClicked: {
            var idx=root.indexAt(mouse.x, mouse.y)
            root.currentIndex=idx
        }
    }
}