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

#ifndef MEMORYTHEME_H
#define MEMORYTHEME_H
#include <QString>
#include <QList>


struct ThemeItem
{
    QString imageName;
    QString soundName;
};

class MemoryTheme
{
    public:
        MemoryTheme(const QString& path);

        QString name() const { return m_name; }
        QString description() const { return m_description; }
        QString backName() const { return m_backName; }
        QString path() const { return m_path; }
        
        QList<ThemeItem> items() const { return m_items; }
        
        bool isCorrect() const { return m_error.isEmpty(); }
        QString error() const { return m_error; }
        
    private:

        QString m_data;
        
        QString m_name;
        QString m_description;
        QString m_backName;
        QList<ThemeItem> m_items;
        
        QString m_error;
        QString m_path;
};

#endif // MEMORYTHEME_H
