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

#ifndef PAIRSTHEMEEDITOR_H
#define PAIRSTHEMEEDITOR_H
#include "../game/pairsthemebase.h"
#include <QtCore/QDir>
#include <QtCore/QXmlStreamReader>
#include <QtGui/QStandardItem>
#include "cardtype.h"

class PairsThemeEditor : public PairsThemeBase
{
    Q_OBJECT

    public:

    	PairsThemeEditor(const QString& path);
        virtual QString path() const;
        virtual QStringList images() const;
        virtual bool hasFile(const QString& path) const;
    private:
        QFile m_archive;
        QDir m_dir;

};

#endif // PAIRSTHEME_H
