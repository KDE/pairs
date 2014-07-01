/*
 * CooperativeTheme.h
 *
 *  Created on: Jan 19, 2014
 *      Author: marcuzzo
 */

#ifndef COOPERATIVETHEME_H_
#define COOPERATIVETHEME_H_

#include "pairsthemebase.h"

class CooperativeTheme: protected PairsThemeBase
{
public:
	CooperativeTheme(const QString& path);
	virtual ~CooperativeTheme();

protected:
	QMap<QString, QString> m_fileSet;
    bool isValid(const KArchiveFile* file);
    //TODO: use KZip everywhere
    #ifdef Q_OS_WIN
            KZip m_archive;
    #else
    		KTar m_archive;
    #endif
	void coopParse(QXmlStreamReader &reader);
	void coopParseElement(QXmlStreamReader &reader);

};

#endif /* COOPERATIVETHEME_H_ */
