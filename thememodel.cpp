#include "thememodel.h"
#include "elementitem.h"
#include <klocale.h>


ThemeModel::ThemeModel(PairsTheme &t, QObject* parent): QStandardItemModel(parent)
{
    QHash<int, QByteArray> names = QStandardItemModel::roleNames();
    names.insert(CardTypeRole, "type");
    names.insert(LanguageRole, "language");
    names.insert(PathRole, "path");
    setRoleNames(names);
    QString name("Element");
	Q_FOREACH(const ThemeElement& el, t.items())
    {
		ElementItem *item = new ElementItem(el);
		QString name = i18n("Element ", rowCount()+1);
		item->setText(name);
		appendRow(item);
    }
}
