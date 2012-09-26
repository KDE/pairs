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
#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <KLocalizedString>
#include <KStandardDirs>
#include <QtXmlPatterns/QXmlSchemaValidator>
#include <QtXmlPatterns/QXmlSchema>
#include "cardtype.h"

CardType PairsTheme::cardNameToType(const QString& name)
{
    if (name == "image")      return CARD_IMAGE;
    else if (name == "image2")return CARD_IMAGE2;
    else if (name == "sound") return CARD_SOUND;
    else if (name == "word")  return CARD_WORD;
    else if (name == "logic") return CARD_LOGIC;
    else if (name == "soundlogic") return CARD_SOUNDLOGIC;
    else if (name == "pfound") return CARD_FOUND;
    Q_ASSERT(false);
    return CARD_NONE;
}

PairsTheme::PairsTheme(const QString& path)
    : QStandardItem()
    , m_back_img("")
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
    if(!isValid(&m_archive))
    {
        qWarning() << "Skipping game theme not valid: " << path;
        m_error = "Not valid XML file";
        return;
    }
    qDebug() << path << m_dir.path();
    QXmlStreamReader reader(&m_archive);
    
    while (m_error.isEmpty() && !reader.atEnd()) {
        QXmlStreamReader::TokenType type = reader.readNext();
        if(type==QXmlStreamReader::StartDocument || type==QXmlStreamReader::EndDocument) {}
        else if (type==QXmlStreamReader::Characters) {}
        else if (type==QXmlStreamReader::EndElement) {}
        else if(type==QXmlStreamReader::StartElement) {
            QString name = reader.name().toString();
            if(name == "title") {
                m_title = reader.readElementText().trimmed();
            } else if(name == "description") {
                m_description = reader.readElementText().trimmed();
            } else if(name == "author") {
                m_author = reader.readElementText().trimmed();
            } else if(name == "version") {
                m_version = reader.readElementText().trimmed();
            } else if(name == "date") {
                m_date = reader.readElementText().trimmed();
            } else if(name == "main") {
                m_main = reader.attributes().value("type").toString();
                m_main_type = cardNameToType(m_main);
            } else if(name == "sound") {
                QStringRef soundtype=reader.attributes().value("type");
                if(soundtype == "missed") {
                    m_missed_snd = reader.attributes().value("src").toString();
                }
                else if(soundtype == "found") {
                    m_found_snd = reader.attributes().value("src").toString();
                }
                else if(soundtype == "turn") {
                    m_turn_snd = reader.attributes().value("src").toString();
                }
            } else if(name == "image") {
                QStringRef imagetype = reader.attributes().value("type");
                if(imagetype == "back") {
                    m_back_img = reader.attributes().value("src").toString();
                }
                else if(imagetype == "trasparent_back") {
                    m_backtrasp_img = reader.attributes().value("src").toString();
                }
                else if(imagetype == "background") {
                    m_background_img = reader.attributes().value("src").toString();
                }
            } else if(name=="element") {
                parseElement(reader);
            }
        }
        else {
            m_error = i18n("%1:%2 Unknown token in theme file", reader.lineNumber(), reader.columnNumber());
        }
    }
  qDebug() << m_title << m_description << m_author << m_date << m_version << m_missed_snd << m_found_snd
              << m_turn_snd << m_back_img << m_background_img << m_backtrasp_img << m_main << m_languages;
    if (reader.hasError()) {
        m_error += reader.errorString();
    }

    setText(title());
    m_archive.close();
//     setIcon(QIcon(backImage()));
//    setData(qVariantFromValue<QStringList>(m_cardtypes["any"].toList()), CardTypeRole);
//    setData(qVariantFromValue<QStringList>(m_languages.toList()), LanguagesRole);
 //   setData(backImage(), Qt::DecorationRole);
}

bool PairsTheme::isPertinent(const QString &type,const QString &lang) {
//     qDebug() << type << lang << m_cardtypes[lang].count(type);
    return (m_cardtypes[lang].contains(type) || m_cardtypes["any"].contains(type));
}

void PairsTheme::parseElement(QXmlStreamReader &reader)
{
    QString common[CARD_MAX_TYPE];
    QString common_found("");
    CardType current_type = CARD_IMAGE;
    common[CARD_LOGIC] = "";
    QXmlStreamReader::TokenType type = reader.readNext();
    ThemeElement item;
    while(!reader.atEnd()) {
        if(type==QXmlStreamReader::EndElement && reader.name().toString() == "element") {
            for (int i = 0; i < CARD_MAX_TYPE; i++) {
                if(!common[i].isEmpty()) {
                    foreach (const QString &str, m_cardtypes.keys()) {
                        if(item.name[i][str].isEmpty())
                            item.name[i][str]=common[i];
                    }
                }
                common[i].clear();
//                 qDebug() << "ITEM" << item.name[i]  << "/ITEM";
            }
            
//             qDebug() << "CTYPES" << m_cardtypes << "/CTYPES";
//             qDebug() << item.foundSound("en");
            m_items += item;
            item.reset();
        }
        else if(type==QXmlStreamReader::StartElement) {
            QString name = reader.name().toString();
            QString lang = reader.attributes().hasAttribute("lang") ? reader.attributes().value("lang").toString() : "any";
            QString src = "";
            m_languages.insert(lang);
            
            if(name != "element") {
                m_cardtypes[lang].insert(name);
            
                current_type = cardNameToType(name);
                if(current_type != CARD_WORD)
                    src = reader.attributes().value("src").toString();
                switch(current_type) {
                    case CARD_IMAGE:
                        if(common[CARD_IMAGE].isEmpty() && item.name[CARD_IMAGE][lang].isEmpty()){
                            item.name[CARD_IMAGE][lang] = src;
                            break;
                        }
                        else {
                            current_type = CARD_IMAGE2;
                            m_cardtypes[lang].insert("image2");
                            m_cardtypes[lang].insert("logic");
                        }
                    case CARD_IMAGE2:
                        item.name[CARD_IMAGE2][lang] = src;
                        item.name[CARD_LOGIC][lang] = src;
                        break;
                    case CARD_SOUNDLOGIC:
                        item.name[CARD_SOUNDLOGIC][lang] = src;
                        break;
                    case CARD_LOGIC:
                        item.name[CARD_LOGIC][lang] = src;
                        break;
                    case CARD_SOUND:
                        m_cardtypes[lang].insert("soundlogic");
                        item.name[CARD_SOUND][lang] = src;
                        item.name[CARD_SOUNDLOGIC][lang] = src;
                        break;
                    case CARD_FOUND:
                        item.found[lang] = src;
                        qDebug() << lang << src << item.found[lang] << item.foundSound("en");
                        break;
                    case CARD_WORD:
                        QString src = reader.readElementText().trimmed();
                        if(current_type == m_main_type)
                            common[current_type] = src;
                        item.name[current_type][lang] = src;
                        break;
                }
                
                if(current_type == m_main_type) {
                    common[current_type] = src;
                    common[CARD_LOGIC] = src;
                }
             }
        }
        type = reader.readNext();
    }
}

bool PairsTheme::isValid(const QFile* file) {

	return true;
    QUrl schemaUrl = QUrl::fromLocalFile(KGlobal::dirs()->findResource("appdata", QLatin1String( "themes/game.xsd" )));
    QXmlSchema schema;
    schema.load(schemaUrl);

    if(!schema.isValid()) {
        qWarning() << "game Schema not valid";
        return false;
    }
    QXmlSchemaValidator validator(schema);
    return validator.validate((QFile*)file);
}

QStringList PairsTheme::images() const
{
	QStringList a("*.svg");
    return m_dir.entryList(a, QDir::Files);
}

bool PairsTheme::hasFile(const QString& path) const
{
    return m_dir.exists(path);
}

QString PairsTheme::path() const
{
    return m_dir.path();
}

QString ThemeElement::value(CardType type, const QString& language) const
{
    QString ret = name[type][language];
    if(ret.isEmpty())
        return name[type]["any"];

    return ret;
}

QStringList ThemeElement::langlist(CardType type) const
{
    return name[type].keys();
}

QString ThemeElement::foundSound(const QString& lang) const
{
    QString ret = found[lang];
    if(ret.isEmpty())
        ret = found["any"];
    return ret;
}
