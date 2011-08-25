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
#include "memorytheme.h"
#include <QDate>
#include <QTimer>
#include <QSvgRenderer>

kmemoryView::kmemoryView(QWidget *parent)
    : QGraphicsView(parent), m_last(0)
{
    setScene(new QGraphicsScene(this));
    
    m_cardsSize=QSizeF(128,128);
    qsrand(QTime::currentTime().msec()*QTime::currentTime().second());
}

kmemoryView::~kmemoryView()
{}

void kmemoryView::cardSelected(CardItem* card)
{
    Q_ASSERT(card);
    
//     qDebug() << "-------" << int(m_last) << int(card);
    if(m_last) {
        if(m_last->data(0)==card->data(0)) {
            m_last->markDone();
            card->markDone();
        } else {
            QTimer::singleShot(500, card, SLOT(turn()));
            QTimer::singleShot(500, m_last, SLOT(turn()));
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

void kmemoryView::newGame(const MemoryTheme& theme, int rows, int columns)
{
    qDeleteAll(m_cards);
    m_cards.clear();
    QList<CardItem*> cards;
    
    QList<ThemeItem> items = theme.items();
    int num=qMin(((rows*columns)/2)*2, items.size()); //we make it %2
    QSvgRenderer backRenderer(theme.backPath());
    for(int i=0; i<num; i++) {
        ThemeItem titem = items.at(i);
        
        for(int j=0; j<2; j++) { //we want pairs
            CardItem* item = new CardItem(&backRenderer, m_cardsSize, NULL, scene());
            item->setData(0, i);
            
            QSvgRenderer imageRenderer(titem.imagePath);
            item->setCardPixmap(&imageRenderer);
            connect(item, SIGNAL(selected(CardItem*)), SLOT(cardSelected(CardItem*)));
            
            cards += item;
        }
    }
    
    while(!cards.isEmpty())
        m_cards += cards.takeAt(qrand()%cards.size());
    
    setRowSize(columns);
}

#include "kmemoryview.moc"
