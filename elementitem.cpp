#include "cardtype.h"
#include "elementitem.h"
#include "featureitem.h"

ElementItem::ElementItem(const ThemeElement &el): QStandardItem()
{
	for(int i = CARD_IMAGE; i < CARD_MAX_TYPE; i++)
	{
		QStringList l = el.langlist((CardType)i);
		if(l.isEmpty() || i == CARD_IMAGE2)
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
