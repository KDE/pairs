#ifndef CARDITEM_H
#define CARDITEM_H

#include <QGraphicsRectItem>
#include <QSvgRenderer>

class QPropertyAnimation;
class QGraphicsRotation;
class CardItem
    : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF position READ pos WRITE setPos);
    public:
        CardItem(QSvgRenderer* back, const QSizeF& size, QGraphicsItem* parent = 0, QGraphicsScene* scene = 0);
        virtual ~CardItem();
        
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
        virtual void mousePressEvent(QGraphicsSceneMouseEvent*) {}
        void setCardPixmap(QSvgRenderer *renderer);
        void markDone();
        
    public slots:
        void emitActivation();
        void changeValue();
        void turn();
        
    signals:
        void selected(CardItem* data);
        
    private:
        QPropertyAnimation* m_animation;
        QPropertyAnimation* m_animationBack;
        
        QSizeF m_size;
        bool m_activated;
        QPixmap m_color;
        QPixmap m_back;
        QPropertyAnimation* m_opacityAnimation;
};

#endif // CARDITEM_H
