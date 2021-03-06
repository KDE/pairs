/*  This file is part of Pairs
 *
 *  Copyright (C) <2012>       <Marco Calignano>     <marco.calignano@gmail.com>
 *
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

#include "featureitem.h"
#include "pairsthemeeditor.h"
#include "thememodel.h"
#include "klocalizedstring.h"
#include <KIcon>
#include <QtCore/QDebug>


FeatureItem::FeatureItem(CardType type, QString lang, QString src): QStandardItem()
{
    setData(type, ThemeModel::CardTypeRole);
    setData(lang, ThemeModel::LanguageRole);
    setData(src, ThemeModel::PathRole);
    QString typeName;
    qDebug() << "creating new feature type:" << type;
    switch(type)
    {
    case CARD_IMAGE:
    case CARD_IMAGE2:
        typeName = "image";
        setIcon(KIcon::fromTheme("view-preview"));
        break;
    case CARD_SOUND:
    case CARD_SOUNDLOGIC:
        typeName = "sound";
        setIcon(KIcon::fromTheme("preferences-desktop-text-to-speech"));
        break;
    case CARD_LOGIC:
        typeName = "logic";
        setIcon(KIcon::fromTheme("preferences-plugin"));
        break;
    case CARD_WORD:
        typeName = "word";
        setIcon(KIcon::fromTheme("preferences-desktop-font"));
        break;
    case CARD_FOUND:
        typeName = "pfound";
        setIcon(KIcon::fromTheme("dialog-ok-apply"));
        break;

    }
    setText(src);
}

void FeatureItem::writeElement(QXmlStreamWriter *stream)
{
    switch(data(ThemeModel::CardTypeRole).toInt())
    {
    case CARD_IMAGE:
    case CARD_LOGIC:
        stream->writeStartElement("image");
        stream->writeAttribute("src", data(ThemeModel::PathRole).toString());
        break;
    case CARD_SOUND:
    case CARD_SOUNDLOGIC:
        stream->writeStartElement("sound");
        stream->writeAttribute("src", data(ThemeModel::PathRole).toString());
        break;
    case CARD_FOUND:
        stream->writeStartElement("pfound");
        stream->writeAttribute("src", data(ThemeModel::PathRole).toString());
        break;
    case CARD_WORD:
        stream->writeStartElement("word");
        break;

    }
    stream->writeAttribute("lang", data(ThemeModel::LanguageRole).toString());
    if(data(ThemeModel::CardTypeRole).toInt() == CARD_WORD)
        stream->writeCharacters(data(ThemeModel::PathRole).toString());
    stream->writeEndElement();
}

bool FeatureItem::check(int index)
{
    m_checkMessage = "";
    if(data(ThemeModel::CardTypeRole).toInt() == 0)
    {
        m_checkMessage = i18n("No features type on child from element %1", index);
        return false;
    }
    if(data(ThemeModel::LanguageRole).toString().isEmpty())
    {
        m_checkMessage = i18n("No language set on child from element %1", index);
        return false;
    }
    if(data(ThemeModel::PathRole).toString().isEmpty())
    {
        m_checkMessage = i18n("No file or word set on child from element %1", index);
        return false;
    }
    return true;

}
