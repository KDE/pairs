#include "carditem.h"
#include <QGraphicsRotation>
#include <QPropertyAnimation>
#include <QPainter>
#include <QGraphicsOpacityEffect>

CardItem::CardItem(QPixmap backImage, const QSizeF& size, QSvgRenderer &renderer, QGraphicsItem* parent, QGraphicsScene* scene)
    : QGraphicsPixmapItem(parent, scene), m_size(size), m_activated(false), m_back(backImage.scaledToWidth(m_size.width()))
{
    const int duration = 200;
    QGraphicsRotation* rotation = new QGraphicsRotation(this);
    rotation->setAxis(Qt::YAxis);
    rotation->setOrigin(QVector3D(m_back.rect().center()));
  
    m_back = backImage.scaledToWidth(m_size.width());
    QPainter pixPainter(&m_back);
    renderer.render(&pixPainter);
   
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

void CardItem::setCardPixmap(QPixmap pix, QSvgRenderer &renderer)
{
    Q_ASSERT(!pix.isNull());
    m_color=pix.scaledToWidth(m_size.width());
    QPainter pixPainter(&m_color);
    renderer.render(&pixPainter);
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

void CardItem::markDone()
{
    m_opacityAnimation->start();
}
