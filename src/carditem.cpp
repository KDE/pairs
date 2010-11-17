#include "carditem.h"
#include <QGraphicsRotation>
#include <QPropertyAnimation>
#include <qbrush.h>

CardItem::CardItem(const QPixmap& backImage, const QSizeF& size, QGraphicsItem* parent, QGraphicsScene* scene)
    : QGraphicsPixmapItem(parent, scene), m_size(size), m_activated(false), m_back(backImage.scaledToWidth(m_size.width()))
{
    m_rotation = new QGraphicsRotation;
    m_rotation->setAxis(Qt::YAxis);
    m_rotation->setOrigin(QVector3D(m_back.rect().center()));
    
    m_animation = new QPropertyAnimation(m_rotation, "angle", m_rotation);
    m_animation->setStartValue(0);
    m_animation->setEndValue(90);
    m_animation->setDuration(300);
    connect(m_animation, SIGNAL(finished()), SLOT(changeValue()));
    
    m_animationBack = new QPropertyAnimation(m_rotation, "angle", m_rotation);
    m_animationBack->setStartValue(90);
    m_animationBack->setEndValue(0);
    m_animationBack->setDuration(300);
    connect(m_animation, SIGNAL(finished()), SLOT(emitActivation()));
    
    setTransformations(QList<QGraphicsTransform*>() << m_rotation);
    
    Q_ASSERT(!m_back.isNull());
    setPixmap(m_back);
}

CardItem::~CardItem()
{
    delete m_rotation;
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

void CardItem::setCardPixmap(const QPixmap& pix)
{
    Q_ASSERT(!pix.isNull());
    m_color=pix.scaledToWidth(m_size.width());
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
    m_animationBack->start();
}
