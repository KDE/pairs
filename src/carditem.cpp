#include "carditem.h"
#include <QGraphicsRotation>
#include <QPropertyAnimation>
#include <qbrush.h>

CardItem::CardItem(const QColor& backColor, const QSizeF& size, QGraphicsItem* parent, QGraphicsScene* scene)
    : QGraphicsRectItem(QRectF(QPointF(), size), parent, scene), m_activated(false), m_color(Qt::green), m_backColor(backColor)
{
    m_rotation = new QGraphicsRotation;
    m_rotation->setAxis(Qt::YAxis);
    m_rotation->setOrigin(QVector3D(rect().center()));
    
    m_animation = new QPropertyAnimation(m_rotation, "angle", m_rotation);
    m_animation->setStartValue(0);
    m_animation->setEndValue(180);
    m_animation->setDuration(300);
    connect(m_animation, SIGNAL(finished()), SLOT(emitActivation()));
    
    setTransformations(QList<QGraphicsTransform*>() << m_rotation);
    QObject::connect(m_animation, SIGNAL(valueChanged(QVariant)), SLOT(valueChanged(QVariant)));
    
    setBrush(backColor);
}

CardItem::~CardItem()
{
    delete m_rotation;
}

void CardItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
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

void CardItem::valueChanged(const QVariant& value)
{
    if(value.toInt()>90) {
        if(m_activated)
            setBrush(m_color);
        else
            setBrush(m_backColor);
    }
}

void CardItem::setCardColor(const QColor& color)
{
    m_color=color;
}

void CardItem::emitActivation()
{
    if(m_activated)
        emit selected(this);
}
