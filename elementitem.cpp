#include "cardtype.h"
#include "elementitem.h"
#include "featureitem.h"

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
		if(l.isEmpty())
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
