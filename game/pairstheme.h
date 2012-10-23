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

#ifndef PAIRSTHEME_H
#define PAIRSTHEME_H
#include "pairsthemebase.h"
#ifdef Q_OS_WIN
#include <KZip>
#else
#include <KTar>
#endif
#include <QtXml/QXmlStreamReader>
#include <QtGui/QStandardItem>
#include "cardtype.h"

class PairsTheme : public PairsThemeBase
{
    Q_OBJECT

    public:

        PairsTheme(const QString& path);

        virtual QString path() const;
        virtual QStringList images() const;
        virtual bool hasFile(const QString& path) const;

        QByteArray themeData(const QString& path) const;
    private:
        bool isValid(const KArchiveFile* file);
        //TODO: use KZip everywhere
        #ifdef Q_OS_WIN
                KZip m_archive;
        #else
        		KTar m_archive;
        #endif

};

#endif // PAIRSTHEME_H
