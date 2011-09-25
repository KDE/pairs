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


CardItem::CardItem(QSvgRenderer *back, const QSizeF& size, Phonon::MediaObject *media, QGraphicsItem* parent, QGraphicsScene* scene) :
QGraphicsPixmapItem(parent, scene),
m_type(CARD_NONE),
m_size(size),
m_activated(false),
m_color(size.toSize()),
m_back(size.toSize()),
m_mediafile(this)
{
    const int duration = 200;
    m_media = media;
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
    connect(m_animation, SIGNAL(finished()), SLOT(emitActivation()));
    
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


void CardItem::setType(int type, QString &file, KTar &archive){
    m_type = type;
    switch(type){
    case CARD_SOUND:
    {

        m_mediafile.setData(((KArchiveFile*)(archive.directory()->entry(file)))->data());
///        void copy(QIODevice *source , QIODevice *target){         target->write(source->readAll());         }
        break;
    }
    case CARD_VIDEO:
    {
        Phonon::VideoPlayer *videoPlayer = new Phonon::VideoPlayer(Phonon::GameCategory, NULL);
      //  createPath(m_media, videoPlayer);
        break;
    }
    case CARD_IMAGE:
    {
        QSvgRenderer imageRenderer(((KArchiveFile*)(archive.directory()->entry(file)))->data());
        setCardPixmap(&imageRenderer);
        break;
    }

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

void CardItem::emitActivation()
{
    if(m_activated)
        emit selected(this);
}

void CardItem::changeValue()
{
    if(m_activated)
        setPixmap(m_color);
    else
        setPixmap(m_back);

    switch(m_type){
    case CARD_SOUND:
        m_media->setCurrentSource(Phonon::MediaSource(&m_mediafile));
        m_media->play();
        break;
    }

    m_animationBack->start();
}

void CardItem::markDone()
{
    m_opacityAnimation->start();
}
