#ifndef CARDITEM_H
#define CARDITEM_H

#include <QGraphicsRectItem>

class QPropertyAnimation;
class QGraphicsRotation;
class CardItem
    : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF position READ pos WRITE setPos);
    public:
        CardItem(const QColor& backColor, const QSizeF& rect, QGraphicsItem* parent = 0, QGraphicsScene* scene = 0);
        virtual ~CardItem();
        
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
        virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) {}
        void turn();
        void setCardColor(const QColor& color);
        
    public slots:
        void valueChanged(const QVariant& value);
        void emitActivation();
        
    signals:
        void selected(CardItem* data);
        
    private:
        QGraphicsRotation* m_rotation;
        QPropertyAnimation* m_animation;
        
        bool m_activated;
        QColor m_color;
        QColor m_backColor;
};

#endif // CARDITEM_H
