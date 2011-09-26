/*
 *  Copyright (C) <2010>       <Aleix Pol>           <aleixpol@kde.org>
 *  Copyright (C) <2011>       <Marco Calignano>     <marco.calignano@gmail.com>
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
#include <KTar>
#include <KDE/KLocale>

#include <Phonon/MediaObject>
#include <Phonon/AudioOutput>
#include <Phonon/VideoPlayer>


CardItem::CardItem(QSvgRenderer *back, const QSizeF& size, QGraphicsItem* parent, QGraphicsScene* scene) :
QGraphicsPixmapItem(parent, scene),
m_type(CARD_NONE),
m_size(size),
m_activated(false),
m_color(size.toSize()),
m_back(size.toSize())
{
    const int duration = 200;
    QGraphicsRotation* rotation = new QGraphicsRotation(this);
    rotation->setAxis(Qt::YAxis);
    rotation->setOrigin(QVector3D(m_back.rect().center()));
    
    m_back.fill(Qt::transparent);
    QPainter p(&m_back);
    back->render(&p);
    
    m_animation = new QPropertyAnimation(rotation, "angle", rotation);
    m_animation->setStartValue(0);
    m_animation->setEndValue(90);
    m_animation->setDuration(duration);
    connect(m_animation, SIGNAL(finished()), SLOT(changeValue()));
    
    m_animationBack = new QPropertyAnimation(rotation, "angle", rotation);
    m_animationBack->setStartValue(90);
    m_animationBack->setEndValue(0);
    m_animationBack->setDuration(duration);
    
    setTransformations(QList<QGraphicsTransform*>() << rotation);
    
    QGraphicsOpacityEffect* opacity = new QGraphicsOpacityEffect(this);
    opacity->setOpacity(1.);
    
    m_opacityAnimation=new QPropertyAnimation(opacity, "opacity", opacity);
//     m_opacityAnimation->setEasingCurve(QEasingCurve::InExpo);
    m_opacityAnimation->setEndValue(0.2);
    setGraphicsEffect(opacity);
    
    Q_ASSERT(!m_back.isNull());
    setPixmap(m_back);
}

CardItem::~CardItem()
{}


void CardItem::setType(CardType type, QString& file, KTar& archive){
    m_type = type;
    switch(type){
        case CARD_SOUND:
        {
            m_color.fill(Qt::blue);
            QBuffer *mediafile = new QBuffer(this);
            mediafile->setData(static_cast<const KArchiveFile*>(archive.directory()->entry(file))->data());
            m_source = Phonon::MediaSource(mediafile);
    ///        void copy(QIODevice *source , QIODevice *target){         target->write(source->readAll());         }
        }   break;
        case CARD_VIDEO:
        {
            Phonon::VideoPlayer *videoPlayer = new Phonon::VideoPlayer(Phonon::GameCategory, NULL);
          //  createPath(m_media, videoPlayer);
            break;
        }
        case CARD_IMAGE:
        {
            QSvgRenderer imageRenderer(static_cast<const KArchiveFile*>(archive.directory()->entry(file))->data());
            setCardPixmap(&imageRenderer);
            break;
        }
        case CARD_WORD:
        {
            m_color.fill(Qt::white);
            QFont myFont;
            myFont.setPointSizeF(22.0);
            myFont.setFamily("Times");
            QPainter paint;
            paint.begin(&m_color);
            paint.setFont(myFont);

            paint.setPen( Qt::blue );
            paint.drawText( m_color.rect(), Qt::AlignCenter, file);
            paint.end();
        }   break;
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

void CardItem::setCardPixmap(QSvgRenderer* renderer)
{
    m_color.fill(Qt::transparent);
    QPainter pixPainter(&m_color);
    renderer->render(&pixPainter);
}

void CardItem::changeValue()
{
    if(m_activated)
        setPixmap(m_color);
    else
        setPixmap(m_back);

    if(m_type==CARD_SOUND && m_activated) {
        Phonon::MediaObject* object = new Phonon::MediaObject(this);
        Phonon::AudioOutput *audioOutput = new Phonon::AudioOutput(Phonon::GameCategory, this);
        createPath(object, audioOutput);
        object->setCurrentSource(m_source);
        object->play();
        connect(object, SIGNAL(finished()), object, SLOT(deleteLater()));
    }

    if(m_activated)
        emit selected(this);

    m_animationBack->start();
}

void CardItem::markDone()
{
    m_opacityAnimation->start();
}
