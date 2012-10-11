/*  This file is part of Pairs
 *
 *  Copyright (C) <2011>       <Marco Calignano>     <marco.calignano@googlemail.com>
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

#ifndef ELEMENTITEM_H
#define ELEMENTITEM_H

#include <QtGui/QStandardItem>
#include "pairstheme.h"

class QXmlStreamWriter;

class ElementItem: public QStandardItem
{
    public:
        explicit ElementItem(const ThemeElement &el);
        void writeElement(QXmlStreamWriter *stream);
        QString checkMessage() const {return m_checkMessage;};
        bool check(int index);
    private:
        QString m_checkMessage;

};

#endif // ELEMENTITEM_H
