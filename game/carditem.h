/*  This file is part of Pairs
 *
 *  Copyright (C) <2010>       <Aleix Pol>           <aleixpol@kde.org>
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

#ifndef CARDITEM_H
#define CARDITEM_H

#include <QStandardItem>
#include <QBuffer>
#include <QImage>
#include <QString>
#include "cardtype.h"

class PairsTheme;

class CardItem
    : public QObject
    , public QStandardItem
{
    Q_OBJECT;
    Q_PROPERTY(QImage frontImage READ readFront);
    Q_PROPERTY(QImage backImage READ readBack);
    Q_PROPERTY(QString postMessage READ readPostMsg);
    Q_PROPERTY(QString text READ readText);
    Q_PROPERTY(QByteArray foundSound READ readFoundSound WRITE setFoundSound);
    Q_PROPERTY(QByteArray missedSound READ readMissedSound WRITE setMissedSound);
    public:
        CardItem(QObject* parent, QImage front, QImage back, QString text, QString postMessage, QByteArray foundSound, QByteArray missedSound, CardType type, int index);
        virtual ~CardItem();
      //  void setType(CardType type, const QString& file, const PairsTheme* theme);
        QByteArray readFoundSound() const;
        void setFoundSound(const QByteArray &found){m_found = found;};
        QByteArray readMissedSound() const;
        void setMissedSound(const QByteArray &missed){m_missed = missed;};
        QImage readBack(){return m_back;};
        QImage readFront(){return m_front;};
        QString readText(){return m_text;};
        QString readPostMsg(){return m_postMessage;};

    private:
        QObject *m_parent;
        CardType m_type;
        QImage m_front;
        QImage m_back;
        QString m_text;
        QString m_postMessage;
        QByteArray m_found;
        QByteArray m_missed;
};

#endif // CARDITEM_H
