/*
 * kmemoryview.cpp
 *
 * Copyright (C) 2008 Albert Astals Cid <aacid@kde.org>
 */

#include "kmemoryview.h"
#include "carditem.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QGraphicsRotation>

kmemoryView::kmemoryView(QWidget *parent)
    : QGraphicsView(parent), m_last(0)
{
    setScene(new QGraphicsScene(this));
    
    const int num=10;
    m_cardsSize=QSizeF(100,100);
    
    for(int i=0; i<num; i++) {
        int it = i%(num/2);
        
        QColor c = QColor::fromHsv(255*it/5, 255, 255);
        CardItem* item = new CardItem(Qt::white, m_cardsSize, 0, scene());
        item->setData(0, it);
        item->setCardColor(c);
        connect(item, SIGNAL(selected(CardItem*)), SLOT(cardSelected(CardItem*)));
        
        m_cards += item;
    }
    
    setRowSize(5);
}

kmemoryView::~kmemoryView()
{}

void kmemoryView::cardSelected(CardItem* card)
{
    Q_ASSERT(card);
    
//     qDebug() << "-------" << int(m_last) << int(card);
    if(m_last) {
        if(m_last->data(0)==card->data(0)) {
            //yay!
        } else {
            m_last->turn();
            card->turn();
        }
        m_last=0;
    } else
        m_last=card;
}

void kmemoryView::setRowSize(int itemsPerRow)
{
    int i=0;
    
    foreach(CardItem* card, m_cards) {
        QPointF p((i%itemsPerRow)*(m_cardsSize.width()+10), (i/itemsPerRow)*(m_cardsSize.height()+10));
        
        QPropertyAnimation* anim = new QPropertyAnimation(card, "position", card);
        anim->setEndValue(p);
        anim->setDuration(1000);
        
        anim->start(QAbstractAnimation::DeleteWhenStopped);
        i++;
    }
}

#include "kmemoryview.moc"
