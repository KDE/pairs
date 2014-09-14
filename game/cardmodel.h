/*  This file is part of Pairs
 *
 *  Copyright (C) <2014>       <Marco Calignano>     <marco.calignano@gmail.com>
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

#ifndef CARDMODEL_H
#define CARDMODEL_H

#include <QStandardItemModel>
#include "carditem.h"

class CardModel : public QStandardItemModel
{
    Q_OBJECT
public:
    enum CardRoles {
        FrontRole = Qt::UserRole + 1,
        BackRole,
        TextRole,
        FoundRole,
        MissedRole,
        PostMessageRole
};

    CardModel(QObject *parent = 0):QStandardItemModel(parent){};
    virtual ~CardModel(){};
    virtual QHash<int, QByteArray> roleNames() const;
    void addCard(CardItem *card){appendRow(card);};
};

#endif
