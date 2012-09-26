#include "featureitem.h"
#include "pairstheme.h"
#include "thememodel.h"

FeatureItem::FeatureItem(CardType type, QString lang, QString src): QStandardItem()
{
	setData(type, ThemeModel::CardTypeRole);
	setData(lang, ThemeModel::LanguageRole);
	setData(src, ThemeModel::PathRole);
	QString typeName;
	switch(type)
	{
	case CARD_IMAGE:
	case CARD_IMAGE2:
		typeName = "image";
		break;
	case CARD_SOUND:
	case CARD_SOUNDLOGIC:
		typeName = "sound";
		break;
	case CARD_LOGIC:
		typeName = "logic";
		break;
	case CARD_WORD:
		typeName = "word";
		break;
	case CARD_FOUND:
		typeName = "pfound";
		break;

	}
	setText(typeName + "-" + lang + "-" + src);
}

