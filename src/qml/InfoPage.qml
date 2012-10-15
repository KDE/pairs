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
    clip: true
    ListView {
        anchors {
            fill: parent
            margins: 5
        }
        spacing: 10
        
        header: Text {
            font.pixelSize: 26
            anchors.horizontalCenter: parent.horizontalCenter
            color: "white"
            font.bold: true
            text: i18n("Pairs 1.0.0")
            height: font.pixelSize*2
        }
        delegate: Column {
            width: parent.width
            spacing: 5
            Text {
                width: parent.width
                wrapMode: Text.WordWrap
                font.pixelSize: 20
                horizontalAlignment: Text.AlignLeft 
                color: "white"
                text: i18n("<b>%1</b> &lt;%2&gt;", name, email)
            }
            Text {
                wrapMode: Text.WordWrap
                width: parent.width
                font.pixelSize: 18
                font.italic: true
                horizontalAlignment: Text.AlignLeft 
                color: "white"
                text: description
            }
        }
        model: authors
        
        property list<Author> authors: [
            Author {
                name: "Aleix Pol Gonzalez"
                email: "aleixpol@kde.org"
                description: i18n("Initial implementation and maintainer")
            },
            Author {
                name: "Marco Calignano"
                email: "marco.calignano@googlemail.com"
                description: i18n("Theme support enhancement and general feature development")
            },
            Author {
                name: "Albert Astals Cid"
                email: "aacid@kde.org"
                description: i18n("Initial project setup and ideas")
            },
            Author {
                name: "Abhash Bikram Thapa"
                email: "abhash@pixelpinch.com"
                description: i18n("Graphic design and icons")
            }
        ]
        footer: Button {
            width: parent.width
            text: i18n("Go back")
            font.pixelSize: 30
            font.bold: true
        }
    }
}
