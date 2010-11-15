/*
 * kmemoryview.cpp
 *
 * Copyright (C) 2008 Albert Astals Cid <aacid@kde.org>
 */

#include "kmemoryview.h"
#include "carditem.h"
#include <QDebug>

kmemoryView::kmemoryView(QWidget *parent)
    : QGraphicsView(parent), m_last(0)
{
    setScene(new QGraphicsScene(this));
    
    for(int i=0; i<5; i++) {
        QColor c = QColor::fromHsv(255*i/5, 255, 255);
        CardItem* item = new CardItem(Qt::black, QRectF(i*110,0,100,100), 0, scene());
        item->setData(0, i);
        item->setCardColor(c);
        connect(item, SIGNAL(selected(CardItem*)), SLOT(cardSelected(CardItem*)));
    }
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

#include "kmemoryview.moc"
