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

#include "pairstheme.h"
#include <QFile>
#include <QDebug>
#include <KLocalizedString>
#include <KStandardDirs>
#include <QXmlSchemaValidator>
#include <QXmlSchema>
#include "cardtype.h"

PairsTheme::PairsTheme(const QString& path)
{
	KTar archive(path);
	m_path = path;
	bool b = archive.open(QIODevice::ReadOnly);
    Q_ASSERT(b);
	QStringList files(archive.directory()->entries());
    files = files.filter(QRegExp("*.game", Qt::CaseSensitive, QRegExp::Wildcard));
    
    Q_ASSERT(!files.isEmpty() && "no games in the theme!");
    
    QString themename(files.first()); //TODO: Support many games inside a theme
    Q_ASSERT(archive.directory()->entry(themename)->isFile());
    const KArchiveFile* file = static_cast<const KArchiveFile*>(archive.directory()->entry(themename));
    if(!isValid(file)){
        qWarning() << "Skipping game theme not valid";
        m_error = "Not valid XML file";
    }

    QXmlStreamReader reader(file->data());
    
    while (m_error.isEmpty() && !reader.atEnd()) {
        QXmlStreamReader::TokenType type = reader.readNext();
        if(type==QXmlStreamReader::StartDocument || type==QXmlStreamReader::EndDocument) {}
        else if (type==QXmlStreamReader::Characters){}
        else if (type==QXmlStreamReader::EndElement){}
        else if(type==QXmlStreamReader::StartElement) {
            QString name = reader.name().toString();
            if(name == "title") {
                m_title = reader.readElementText();
            }
            if(name == "description") {
                m_description = reader.readElementText();
            }
            if(name == "author") {
                m_author = reader.readElementText();
            }
            if(name == "version") {
                m_version = reader.readElementText();
            }
            if(name == "date") {
                m_date = reader.readElementText();
            }
            if(name == "main") {
                m_main = reader.attributes().value("type").toString();
                if (m_main == "image") m_main_type = CARD_IMAGE;
                if (m_main == "image2") m_main_type = CARD_IMAGE2;
                if (m_main == "sound") m_main_type = CARD_SOUND;
                if (m_main == "video") m_main_type = CARD_VIDEO;
                if (m_main == "word") m_main_type = CARD_WORD;


            }
            if(name == "sound") {
                if(reader.attributes().value("type") == "missed"){
                    m_missed_snd = reader.attributes().value("src").toString();
                }
                if(reader.attributes().value("type") == "found"){
                    m_found_snd = reader.attributes().value("src").toString();
                }
                if(reader.attributes().value("type") == "turn"){
                    m_turn_snd = reader.attributes().value("src").toString();
                }
            }

            if(name == "image") {
                if(reader.attributes().value("type") == "back"){
                    m_back_img = reader.attributes().value("src").toString();
                }
                if(reader.attributes().value("type") == "trasparent_back"){
                    m_backtrasp_img = reader.attributes().value("src").toString();
                }
                if(reader.attributes().value("type") == "bakcground"){
                    m_background_img = reader.attributes().value("src").toString();
                }
            }

            if(name=="element") {
                parseElement(reader);
            }
        }
        else {
            m_error = i18n("%1:%2 Unknown token in theme file", reader.lineNumber(), reader.columnNumber());
        }
    }
    qDebug() << m_title << m_description << m_author << m_date << m_version << m_missed_snd << m_found_snd
             << m_turn_snd << m_back_img << m_background_img << m_backtrasp_img << m_main << m_languages;
    if (reader.hasError()) {}
}

void PairsTheme::parseElement(QXmlStreamReader &reader)
{
    QString common[CARD_MAX_TYPE];
    CardType current_type = CARD_IMAGE;
    QStringList commonname;
    common[CARD_IMAGE] = "";
    common[CARD_IMAGE2] = "";
    common[CARD_SOUND] = "";
    common[CARD_VIDEO] = "";
    common[CARD_WORD] = "";
    QXmlStreamReader::TokenType type = reader.readNext();
    ThemeElement item;
    while(!reader.atEnd()){
        if(type==QXmlStreamReader::EndElement && reader.name().toString() == "element") {


            for (int i = 0; i < CARD_MAX_TYPE; i++){
                if(!common[i].isEmpty()){
                    foreach (const QString &str, m_cardtypes.keys()){
                        item.name[i][str].append(common[i]);
                    }
                }
                common[i] = "";
                qDebug() << "ITEM" << item.name[i]  << "/ITEM";
            }
            foreach (const QString &str, m_cardtypes.keys()){
                m_cardtypes[str].append(commonname);
                m_cardtypes[str].removeDuplicates();
                m_cardtypes[str].sort();
            }
            qDebug() << "CTYPES" << m_cardtypes << "/CTYPES";
            m_items += item;
            item.reset();
        }
        else
        if(type==QXmlStreamReader::StartElement) {
            QString name = reader.name().toString();
            QString l = reader.attributes().value("lang").toString();
            if(!l.isEmpty() && m_languages.lastIndexOf(l) == -1){
                m_languages.append(l);
            }
            if(name != "element"){
                if(l.isEmpty() && commonname.count(name) == 0)
                    commonname.append(name);
                if(!l.isEmpty()  && m_cardtypes[l].count(name) == 0)
                    m_cardtypes[l].append(name);
            }
            if(name == "image") {
                if(common[CARD_IMAGE].isEmpty() && item.name[CARD_IMAGE][l].isEmpty())
                    current_type = CARD_IMAGE;
                else
                    current_type = CARD_IMAGE2;
            }
            if(name == "sound") {
                current_type = CARD_SOUND;
            }
            if(name == "video") {
                current_type = CARD_VIDEO;
            }
            if(name == "word") {
                current_type = CARD_WORD;
                if(l.isEmpty()) {
                    common[current_type] = reader.readElementText();
                }
                else{
                    if(current_type == m_main_type)
                        common[current_type] = reader.readElementText();
                    item.name[current_type][l] = reader.readElementText();
                }
            }
            if(name != "element" && name != "word") {
                if(l.isEmpty()) {

                    common[current_type] = reader.attributes().value("src").toString();
                }
                else{
                    if(current_type == m_main_type)
                        common[current_type] = reader.attributes().value("src").toString();
                    item.name[current_type][l] = reader.attributes().value("src").toString();
                }
            }
        }
        type = reader.readNext();
    }

        

   // qDebug() << m_languages << m_cardtypes;
   
   
}

bool PairsTheme::isValid(const KArchiveFile* file){

    QUrl schemaUrl(KGlobal::dirs()->findResource("appdata", QLatin1String( "themes/game.xsd" )));
    QXmlSchema schema;
    schema.load(schemaUrl);

    if(!schema.isValid()){
        qWarning() << "game Schema not valid";
        return false;
    }
    QXmlSchemaValidator validator(schema);
    return validator.validate(file->data());
}
