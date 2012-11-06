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

#include "thememodel.h"
#include "elementitem.h"
#include <klocale.h>


ThemeModel::ThemeModel(PairsThemeEditor &t, QObject* parent): QStandardItemModel(parent)
{
    QHash<int, QByteArray> names = QStandardItemModel::roleNames();
    names.insert(CardTypeRole, "type");
    names.insert(LanguageRole, "language");
    names.insert(PathRole, "path");
    setRoleNames(names);
    Q_FOREACH(const ThemeElement& el, t.items())
    {
        ElementItem *item = new ElementItem(el);
        QString name = i18n("Element %1", el.value(CARD_IMAGE, "any").split('.').first());
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
    reset();
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
