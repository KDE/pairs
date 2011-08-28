/*
 *  Copyright (C) <2010>       <Aleix Pol>           <aleixpol@kde.org>
 *  Copyright (C) <2011>       <Marco Calignano>     <marco.calignano@gmail.com>
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

#include "memorytheme.h"
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>
#include <KLocalizedString>
#include <KTar>

MemoryTheme::MemoryTheme(const QString& path)
{
	KTar archive(path);
	m_path = path;
	archive.open(QIODevice::ReadOnly);
	QStringList files(archive.directory()->entries());
	QString themename(files[ files.lastIndexOf(QRegExp ("*.game", Qt::CaseSensitive, QRegExp::Wildcard))]);
	
    QXmlStreamReader reader(((KArchiveFile*)(archive.directory()->entry(themename)))->data());
    
    while (m_error.isEmpty() && !reader.atEnd()) {
        QXmlStreamReader::TokenType type = reader.readNext();
        
        if(type==QXmlStreamReader::StartDocument || type==QXmlStreamReader::EndDocument) {}
        else if (type==QXmlStreamReader::Characters)
            m_data += reader.text().toString();
        else if(type==QXmlStreamReader::StartElement) {
            m_data.clear();
            
            QString name = reader.name().toString();
         
            if(name=="card") {
                ThemeItem item;
                item.imageName = reader.attributes().value("image").toString();
                item.soundName = reader.attributes().value("sound").toString();
                m_items += item;
            }
        } else if (type==QXmlStreamReader::EndElement) {
           //  qDebug() << "ssssss" << m_data << type;
            QString name = reader.name().toString();
            
            if(name=="description") m_description = m_data;
            else if(name=="description") m_name = m_data;
            else if(name=="back") m_backName = m_data;
            else if(name=="name") m_name = m_data;
            else if(name=="card" || name=="memory") {}
            else
                m_error = i18n("Unknown item '%1' found", reader.name().toString());
        } else {
            m_error = i18n("%1:%2 Unknown token in theme file", reader.lineNumber(), reader.columnNumber());
        }
    }
    
    if (reader.hasError()) {}
}

