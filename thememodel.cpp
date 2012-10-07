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
	Q_FOREACH(const ThemeElement& el, t.items())
    {
		ElementItem *item = new ElementItem(el);
		QString name = i18n("Element %1", rowCount()+1);
		item->setText(name);
		appendRow(item);
    }
}

ThemeModel::ThemeModel(QObject* parent): QStandardItemModel(parent)
{
    QHash<int, QByteArray> names = QStandardItemModel::roleNames();
    names.insert(CardTypeRole, "type");
    names.insert(LanguageRole, "language");
    names.insert(PathRole, "path");
    setRoleNames(names);
    ElementItem *item = new ElementItem(ThemeElement());
    QString name = i18n("Element %1", rowCount()+1);
    item->setText(name);
    appendRow(item);
}

void ThemeModel::removeItem(QStandardItem *selectedItem)
{

    QStandardItem *par = selectedItem->parent();

    QModelIndex mi = indexFromItem(selectedItem);

    if (par) {
        beginRemoveRows(mi, mi.row(), mi.row());
        par->removeRow(mi.row());
    }
    else
    {
        beginRemoveRows(QModelIndex(), mi.row(), mi.row());
        removeRow(mi.row());
    }

    endRemoveRows();

}

void ThemeModel::insertItem(QStandardItem *newItem)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    insertRow(rowCount(), newItem);
    endInsertRows();
}

void ThemeModel::insertFeature(QStandardItem *newItem, QStandardItem *parent)
{
    beginInsertRows(indexFromItem(parent), parent->row(), parent->row());
    parent->appendRow(newItem);
    endInsertRows();
}
