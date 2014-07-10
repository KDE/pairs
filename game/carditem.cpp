/*  This file is part of Pairs
 *
 *  Copyright (C) <2010>       <Aleix Pol>           <aleixpol@kde.org>
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

#include "carditem.h"
#include <QFile>
#include <KDE/KLocale>
#include <KStandardDirs>

CardItem::CardItem(QObject* parent, QImage front, QImage back, QString text, QString postMessage, QByteArray foundSound, QByteArray missedSound, CardType type, int index)
    : QObject(parent)
	, QStandardItem()
    , m_type(type)
	, m_front(front)
    , m_back(back)
    , m_text(text)
    , m_postMessage(postMessage)
    , m_found(foundSound)
    , m_missed(missedSound)
{
	m_parent = parent;
	m_index = index;
}

CardItem::~CardItem()
{}

QByteArray CardItem::readFoundSound() const
{
    if(m_found.isEmpty()) {
        static QByteArray defaultCorrectSound;
        if(defaultCorrectSound.isEmpty()) {
        	QFile file(QStandardPaths::locate(QStandardPaths::DataLocation, QLatin1String("themes/right.ogg")));
            if (!file.open(QIODevice::ReadOnly)) return defaultCorrectSound;
            defaultCorrectSound = file.readAll();
        }
        return defaultCorrectSound;
    } else
        return m_found;
}

QByteArray CardItem::readMissedSound() const
{
    if(m_missed.isEmpty()) {
        static QByteArray defaultMissedSound;
        if(defaultMissedSound.isEmpty()) {
        	QFile file(QStandardPaths::locate(QStandardPaths::DataLocation, QLatin1String("themes/wrong.ogg")));
            if (!file.open(QIODevice::ReadOnly)) return defaultMissedSound;
            defaultMissedSound = file.readAll();
        }
        return defaultMissedSound;
    } else
        return m_missed;
}

