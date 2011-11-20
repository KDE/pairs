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

#include "carditem.h"
#include <QGraphicsRotation>
#include <QPropertyAnimation>
#include <QPainter>
#include <QGraphicsOpacityEffect>
#include <KDE/KLocale>

#include <Phonon/MediaObject>
#include <Phonon/AudioOutput>
#include <Phonon/VideoPlayer>
#include "pairstheme.h"
#include <kfontutils.h>

CardItem::CardItem(const QSharedPointer<QSvgRenderer>& back, QGraphicsItem* parent, QGraphicsScene* scene)
    : QGraphicsPixmapItem(parent, scene)
    , m_type(CARD_NONE)
    , m_activated(false)
    , m_backRenderer(back)
{

    m_rotation = new QGraphicsRotation(this);
    m_rotation->setAxis(Qt::YAxis);
    
    m_animation = new QPropertyAnimation(m_rotation, "angle", m_rotation);
    m_animation->setStartValue(0);
    m_animation->setEndValue(90);
    connect(m_animation, SIGNAL(finished()), SLOT(changeValue()));
    
    m_animationBack = new QPropertyAnimation(m_rotation, "angle", m_rotation);
    m_animationBack->setStartValue(90);
    m_animationBack->setEndValue(0);
    
    setTransformations(QList<QGraphicsTransform*>() << m_rotation);
    
    QGraphicsOpacityEffect* opacity = new QGraphicsOpacityEffect(this);
    opacity->setOpacity(1.);
    
    m_opacityAnimation=new QPropertyAnimation(opacity, "opacity", opacity);
//     m_opacityAnimation->setEasingCurve(QEasingCurve::InExpo);
    m_opacityAnimation->setEndValue(0.2);
    setGraphicsEffect(opacity);
    
    setDuration(200);
}

CardItem::~CardItem()
{}

void CardItem::setSize(const QSizeF& newSize)
{
    if(newSize==m_back.size())
        return;
    
    m_back=QPixmap(newSize.toSize());
    m_back.fill(Qt::transparent);
    QPainter p(&m_back);
    m_backRenderer->render(&p);
    m_rotation->setOrigin(QVector3D(m_back.rect().center()));
    
    m_color=QPixmap(newSize.toSize());
    m_color.fill(Qt::transparent);
    if(m_type==CARD_WORD) {
        QPainter paint(&m_color);
        KFontUtils::adaptFontSize(paint, m_text, newSize);
        paint.drawText( m_color.rect(), Qt::AlignCenter, m_text);
    } else {
        QPainter pixPainter(&m_color);
        m_frontRenderer->render(&pixPainter);
    }
    
    setPixmap(m_back);
}

void CardItem::setDuration(int dur)
{
    m_animation->setDuration(dur);
    m_animationBack->setDuration(dur);
}

void CardItem::setType(CardType type, QString& file, const PairsTheme* theme){
    m_type = type;
    switch(type){
        case CARD_SOUND:
        {
            m_color.fill(Qt::blue);
            QBuffer *mediafile = new QBuffer(this);
            mediafile->setData(theme->themeData(file));
            m_source = Phonon::MediaSource(mediafile);
    ///        void copy(QIODevice *source , QIODevice *target){         target->write(source->readAll());         }
        }   break;
        case CARD_VIDEO:
        {
//             Phonon::VideoPlayer *videoPlayer = new Phonon::VideoPlayer(Phonon::GameCategory, NULL);
          //  createPath(m_media, videoPlayer);
            break;
        }
        case CARD_IMAGE:
            setCardPixmap(QSharedPointer<QSvgRenderer>(new QSvgRenderer(theme->themeData(file))));
            break;
        case CARD_IMAGE2:
            setCardPixmap(QSharedPointer<QSvgRenderer>(new QSvgRenderer(theme->themeData(file))));
            break;
        case CARD_LOGIC:
            setCardPixmap(QSharedPointer<QSvgRenderer>(new QSvgRenderer(theme->themeData(file))));
            setPixmap(m_color); //TODO: marco! can you explain this to me?
            break;
        case CARD_WORD:
            m_text = file;
            break;
        default:
            break;
    }

}


void CardItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* )
{
    if(!m_activated) {
        turn();
    }
}

void CardItem::turn()
{
    m_activated=!m_activated;
    
    m_animation->start();
}

void CardItem::setCardPixmap(const QSharedPointer<QSvgRenderer>& renderer)
{
    m_frontRenderer=renderer;
}

void CardItem::changeValue()
{
    if(m_activated)
        setPixmap(m_color);
    else{
        if(m_type == CARD_LOGIC)
            setPixmap(m_color);
        else
            setPixmap(m_back);
    }

    if(m_type==CARD_SOUND && m_activated) {
        Phonon::MediaObject* object = new Phonon::MediaObject(this);
        Phonon::AudioOutput *audioOutput = new Phonon::AudioOutput(Phonon::GameCategory, object);
        createPath(object, audioOutput);
        object->setCurrentSource(m_source);
        object->play();
        
        //We delay the emit selected until it has played, that way sounds don't overlap
        connect(object, SIGNAL(finished()), this, SLOT(emitSelected()));
        connect(object, SIGNAL(finished()), object, SLOT(deleteLater()));
    } else if(m_activated)
        emitSelected();

    m_animationBack->start();
}

void CardItem::emitSelected()
{
    emit selected(this);
}

void CardItem::markDone()
{
    m_opacityAnimation->start();
}

bool CardItem::isDone() const
{
    return opacity()<1;
}
