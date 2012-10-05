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
	    setIcon(QIcon(":/images/view-preview.png"));
		break;
	case CARD_SOUND:
	case CARD_SOUNDLOGIC:
		typeName = "sound";
	    setIcon(QIcon(":/images/preferences-desktop-text-to-speech.png"));
		break;
	case CARD_LOGIC:
		typeName = "logic";
	    setIcon(QIcon(":/images/preferences-plugin.png"));
		break;
	case CARD_WORD:
		typeName = "word";
	    setIcon(QIcon(":/images/preferences-desktop-font.png"));
		break;
	case CARD_FOUND:
		typeName = "pfound";
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
