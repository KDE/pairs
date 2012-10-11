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

#include "cardtype.h"
#include "elementitem.h"
#include "featureitem.h"
#include "klocalizedstring.h"
#include <QtXml/QXmlStreamWriter>
#include <QtCore/QDebug>

ElementItem::ElementItem(const ThemeElement &el): QStandardItem()
{
    QStringList l = el.foundLanglist();
    if(!l.isEmpty())
    {
        Q_FOREACH(QString s, l)
        {
            if(!s.isEmpty())
            {
                FeatureItem *item = new FeatureItem(CARD_FOUND, s, el.foundSound(s));
                appendRow(item);
            }
        }
    }
    for(int i = CARD_IMAGE; i < CARD_MAX_TYPE; i++)
    {
        QStringList l = el.langlist((CardType)i);
        if(l.isEmpty() || i == CARD_SOUNDLOGIC || i == CARD_IMAGE2)
            continue;
        Q_FOREACH(QString s, l)
        {
            if(!s.isEmpty())
            {
                FeatureItem *item = new FeatureItem((CardType)i, s, el.value((CardType)i, s));
                appendRow(item);
            }
        }
    }
}


void ElementItem::writeElement(QXmlStreamWriter *stream)
{
    stream->writeStartElement("element");
    for (int i=0; i < rowCount(); i++)
    {
        FeatureItem *item = static_cast<FeatureItem*> (child(i,0));
        item->writeElement(stream);
    }
    stream->writeEndElement();
}

bool ElementItem::check(int index)
{
    m_checkMessage = "";
    if(rowCount() == 0)
    {
        m_checkMessage = i18n("No features present on Element %1", index);
        return false;
    }
    for (int i=0; i < rowCount(); i++)
    {
        FeatureItem *item = static_cast<FeatureItem*> (child(i,0));
        if(!item->check(index))
        {
            m_checkMessage = item->checkMessage();
            return false;
        }

    }
    return true;
}
