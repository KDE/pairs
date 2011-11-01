/*
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

#include <QGraphicsRectItem>
#include <QSvgRenderer>
#include <QBuffer>

#include <KTar>
#include "cardtype.h"
#include <phonon/mediasource.h>

namespace Phonon { class MediaObject; class MediaSource;}

class QPropertyAnimation;
class QGraphicsRotation;
class CardItem
    : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF position READ pos WRITE setPos);
    public:
        CardItem(QSvgRenderer* back, const QSizeF& size, QGraphicsItem* parent, QGraphicsScene* scene = 0);
        virtual ~CardItem();
        
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
        virtual void mousePressEvent(QGraphicsSceneMouseEvent*) {}
        void setCardPixmap(QSvgRenderer *renderer);
        void markDone();
        void setType(CardType type, QString &file, KTar &archive);
        bool isDone() const;
        void setDuration(int dur);
    public slots:
        void changeValue();
        void turn();
        void emitSelected();
        
    signals:
        void selected(CardItem* data);
        
    private:
        QPropertyAnimation* m_animation;
        QPropertyAnimation* m_animationBack;
        
        CardType m_type;
        QSizeF m_size;
        bool m_activated;
        QPixmap m_color;
        QPixmap m_back;
        QPropertyAnimation* m_opacityAnimation;
        Phonon::MediaSource m_source;
};

#endif // CARDITEM_H
