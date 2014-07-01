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

#include "pairstheme.h"
#include <QtCore/QDebug>
#include <KLocalizedString>
#include <KUrl>
#include <KStandardDirs>
#include <QtXmlPatterns/QXmlSchemaValidator>
#include <QtXmlPatterns/QXmlSchema>

PairsTheme::PairsTheme(const QString& path)
    : PairsThemeBase()
	, m_archive(path)
{
	bool b = m_archive.open(QIODevice::ReadOnly);
    Q_ASSERT(b);
	QStringList files(m_archive.directory()->entries());
	files = files.filter(QRegExp("*.game", Qt::CaseSensitive, QRegExp::Wildcard));

    Q_ASSERT(files.count()>=1 && "no games in the theme!");

    QString themename(files.first()); //TODO: Support many games inside a theme
    Q_ASSERT(m_archive.directory()->entry(themename)->isFile());
    const KArchiveFile* file = static_cast<const KArchiveFile*>(m_archive.directory()->entry(themename));
    if(!isValid(file)) {
        qWarning() << "Skipping game theme not valid: " << themename;
        m_error = "Not valid XML file";
    }

    QXmlStreamReader reader(file->data());
    parse(reader);
//     setIcon(QIcon(backImage()));
    setData(qVariantFromValue<QStringList>(m_cardtypes["any"].toList()), CardTypeRole);
    setData(qVariantFromValue<QStringList>(m_languages.toList()), LanguagesRole);
    setData(backImage(), Qt::DecorationRole);
}


bool PairsTheme::isValid(const KArchiveFile* file) {

    KUrl schemaUrl = KUrl::fromLocalFile(KGlobal::dirs()->findResource("appdata", QLatin1String( "themes/game.xsd" )));
    QXmlSchema schema;
    schema.load(schemaUrl);

    if(!schema.isValid()) {
        qWarning() << "game Schema not valid";
        return false;
    }
    QXmlSchemaValidator validator(schema);
    return validator.validate(file->data());
}

QStringList PairsTheme::images() const
{
    QStringList files(m_archive.directory()->entries());
    return files.filter(QRegExp("*.svg", Qt::CaseSensitive, QRegExp::Wildcard));
}

QByteArray PairsTheme::themeData(const QString& path) const
{
    const KArchiveEntry* entry = m_archive.directory()->entry(path);
    if(!entry || !entry->isFile())
        return QByteArray();

    return static_cast<const KArchiveFile*>(entry)->data();
}

bool PairsTheme::hasFile(const QString& path) const
{
    return m_archive.directory()->entries().contains(path);
}

QString PairsTheme::path() const
{
    return m_archive.fileName();
}
