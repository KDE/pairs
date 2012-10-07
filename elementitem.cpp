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
