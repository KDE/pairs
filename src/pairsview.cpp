/*
 *  Copyright (C) <2008>       <Albert Astals Cid>   <aacid@kde.org>
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

#include "pairsview.h"
#include "carditem.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QGraphicsRotation>
#include "pairstheme.h"
#include <QDate>
#include <QTimer>
#include <QSvgRenderer>
#include <KTar>

PairsView::PairsView(QWidget *parent)
    : QGraphicsView(parent), m_last(0)
{
    QObject::connect(this, SIGNAL(pair_missed()), parent, SLOT(inc_missed()));
    QObject::connect(this, SIGNAL(pair_found()), parent, SLOT(inc_found()));
    setScene(new QGraphicsScene(this));
    
    m_cardsSize=QSizeF(128,128);
    qsrand(QTime::currentTime().msec()*QTime::currentTime().second());
}

PairsView::~PairsView()
{}

void PairsView::cardSelected(CardItem* card)
{
    Q_ASSERT(card);
    
//     qDebug() << "-------" << int(m_last) << int(card);
    if(m_last) {
        if(m_last->data(0)==card->data(0)) {
            m_last->markDone();
            card->markDone();
            emit pair_found();
        } else {
            QTimer::singleShot(500, card, SLOT(turn()));
            QTimer::singleShot(500, m_last, SLOT(turn()));
            emit pair_missed();
        }
        m_last=0;
    } else
        m_last=card;
}

int PairsView::cardsNum()
{
   return m_cards.count();
}


void PairsView::setRowSize(int itemsPerRow)
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

void PairsView::newGame(const MemoryTheme& theme)
{
    qDeleteAll(m_cards);
    m_cards.clear();
    QList<CardItem*> cards;
	KTar archive(theme.path());
	archive.open(QIODevice::ReadOnly);
    
    QList<ThemeItem> items = theme.items();
    //int num=qMin(((rows*columns)/2)*2, items.size()); //we make it %2
    int num = items.size();
    QSvgRenderer backRenderer(((KArchiveFile*)(archive.directory()->entry(theme.backName())))->data());
    for(int i=0; i<num; i++) {
        ThemeItem titem = items.at(i);
        
        for(int j=0; j<2; j++) { //we want pairs
            CardItem* item = new CardItem(&backRenderer, m_cardsSize, NULL, scene());
            item->setData(0, i);
            
            QSvgRenderer imageRenderer(((KArchiveFile*)(archive.directory()->entry(titem.imageName)))->data());
            item->setCardPixmap(&imageRenderer);
            connect(item, SIGNAL(selected(CardItem*)), SLOT(cardSelected(CardItem*)));
            cards += item;
        }
    }
    
    while(!cards.isEmpty())
        m_cards += cards.takeAt(qrand()%cards.size());
    if(num % 2 == 0)
    	setRowSize(qMax(4, num/2));
    else
    	setRowSize((2*num)/3);
}

#include "pairsview.moc"