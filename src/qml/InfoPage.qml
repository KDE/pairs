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
 //       anchors.fill: parent
        anchors.horizontalCenter: parent.horizontalCenter
        Text {
            font.pixelSize: 26
            anchors.horizontalCenter: parent.horizontalCenter
            text: i18n("<b>pairs v 0.2.0</b>")
        }
        Text {
            font.pixelSize: 14
            horizontalAlignment: Text.AlignLeft 
            text: " "
        }
        Text {
            font.pixelSize: 20
            horizontalAlignment: Text.AlignLeft 
            text: i18n("<b>Aleix Pol Gonzalez</b> - aleixpol@kde.org")
        }
        Text {
            font.pixelSize: 18
            horizontalAlignment: Text.AlignLeft 
            text: i18n("<i>Initial implementation and maintainer</i>")
        }
        Text {
            font.pixelSize: 12
            horizontalAlignment: Text.AlignLeft 
            text: " "
        }
        Text {
            font.pixelSize: 20
            horizontalAlignment: Text.AlignLeft 
            text: i18n("<b>Marco Calignano</b> - marco.calignano@googlemail.com")
        }
        Text {
            font.pixelSize: 18
            horizontalAlignment: Text.AlignLeft 
            text: i18n("<i>Theme support enhancement and general feature development</i>")
        }
        Text {
            font.pixelSize: 12
            horizontalAlignment: Text.AlignLeft 
            text: " "
        }
        Text {
            font.pixelSize: 20
            horizontalAlignment: Text.AlignLeft 
            text: i18n("<b>Albert Astals Cid</b> - aacid@kde.org")
        }
        Text {
            font.pixelSize: 18
            horizontalAlignment: Text.AlignLeft 
            text: i18n("<i>Initial project setup and ideas</i>")
        }
        Text {
            font.pixelSize: 12
            horizontalAlignment: Text.AlignLeft 
            text: " "
        }
        Text {
            font.pixelSize: 20
            horizontalAlignment: Text.AlignLeft 
            text: i18n("<b>Abhash Bikram Thapa</b> - abhash@pixelpinch.com")
        }
        Text {
            font.pixelSize: 18
            horizontalAlignment: Text.AlignLeft 
            text: i18n("<i>Graphic design and icons</i>")
        }
    }
}