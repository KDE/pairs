/*
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
            font.pixelSize: 20
            anchors.horizontalCenter: parent.horizontalCenter
            text: i18n("pairs v 0.2.0")
        }
        Text {
            font.pixelSize: 20
            anchors.horizontalCenter: parent.horizontalCenter
            text: i18n("Aleix Pol Gonzalez - Initial implementation and maintainer - aleixpol@kde.org")
        }
        Text {
            font.pixelSize: 20
            anchors.horizontalCenter: parent.horizontalCenter
            text: i18n("Marco Calignano - Theme support enhancement and general feature development - marco.calignano@googlemail.com")
        }
        Text {
            font.pixelSize: 20
            anchors.horizontalCenter: parent.horizontalCenter
            text: i18n("Albert Astals Cid - Initial project setup and ideas - aacid@kde.org")
        }
        Text {
            font.pixelSize: 20
            anchors.horizontalCenter: parent.horizontalCenter
            text: i18n("Abhash Bikram Thapa - Graphic design and icons - abhash@pixelpinch.com")
        }
    }
}