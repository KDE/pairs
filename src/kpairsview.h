/*
 *  Copyright (C) <2007>       <Albert Astals Cid>   <aacid@kde.org>
 *  Copyright (C) <2010>       <Aleix Pol>           <aleixpol@kde.org>
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


#ifndef KMEMORYVIEW_H
#define KMEMORYVIEW_H

#include <QtGui/QGraphicsView>

class MemoryTheme;
class CardItem;
class kpairsView : public QGraphicsView
{
    Q_OBJECT
public:
    /**
     * Default constructor
     */
    kpairsView(QWidget *parent);

    /**
     * Destructor
     */
    virtual ~kpairsView();
    
    void setRowSize(int itemsPerRow);
    void newGame(const MemoryTheme& theme, int rows, int columns);
    int cardsNum();

signals:
    void pair_missed();
    void pair_found();
    
public slots:
    void cardSelected(CardItem* cardData);
    
private:
    CardItem* m_last;
    QList<CardItem*> m_cards;
    QSizeF m_cardsSize;
};

#endif // kpairsVIEW_H
