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

#include "pairsthemeeditor.h"
#include <QtCore/QDebug>
#include <KLocalizedString>
#include <QtXmlPatterns/QXmlSchemaValidator>
#include <QtXmlPatterns/QXmlSchema>

PairsThemeEditor::PairsThemeEditor(const QString& path)
    : PairsThemeBase()
	, m_archive(path)
	, m_dir()
{
    QFileInfo fi(path);
    m_dir = fi.dir();
    if (!m_archive.open(QFile::ReadOnly | QFile::Text))
    {
            qWarning() << "Error: Cannot read file " << path;
            return;
    }
    QXmlStreamReader reader(&m_archive);
    parse(reader);
    m_archive.close();
//     setIcon(QIcon(backImage()));
//    setData(qVariantFromValue<QStringList>(m_cardtypes["any"].toList()), CardTypeRole);
//    setData(qVariantFromValue<QStringList>(m_languages.toList()), LanguagesRole);
 //   setData(backImage(), Qt::DecorationRole);
}

QStringList PairsThemeEditor::images() const
{
    QStringList a("*.svg");
    return m_dir.entryList(a, QDir::Files);
}

bool PairsThemeEditor::hasFile(const QString& path) const
{
    return m_dir.exists(path);
}

QString PairsThemeEditor::path() const
{
    return m_dir.path();
}
