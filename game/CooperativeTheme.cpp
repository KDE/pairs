/*
 * CooperativeTheme.cpp
 *
 *  Created on: Jan 19, 2014
 *      Author: marcuzzo
 */

#include "CooperativeTheme.h"

CooperativeTheme::CooperativeTheme(const QString& path)
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
    coopParse(reader);
}

CooperativeTheme::~CooperativeTheme()
{
	// TODO Auto-generated destructor stub
}

