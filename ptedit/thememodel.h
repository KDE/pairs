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
#ifndef THEMEMODEL_H
#define THEMEMODEL_H

#include <QtGui/QStandardItemModel>
#include "pairstheme.h"
class ThemeModel : public QStandardItemModel
{
    Q_OBJECT
    public:
    enum ThemeModelRoles {
         CardTypeRole = Qt::UserRole + 1,
         LanguageRole,
         PathRole
     };
        explicit ThemeModel(PairsTheme &t, QObject* parent = 0);
        explicit ThemeModel(QObject* parent = 0);
        void removeItem(QStandardItem *selectedItem);
        void insertItem(QStandardItem *newItem);
        void insertFeature(QStandardItem *newItem, QStandardItem *parent);
};

#endif // THEMEMODEL_H
