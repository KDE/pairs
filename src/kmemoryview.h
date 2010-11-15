/*
 * kmemoryview.h
 *
 * Copyright (C) 2007 Albert Astals Cid <aacid@kde.org>
 */

#ifndef KMEMORYVIEW_H
#define KMEMORYVIEW_H

#include <QtGui/QGraphicsView>

class CardItem;
class kmemoryView : public QGraphicsView
{
    Q_OBJECT
public:
    /**
     * Default constructor
     */
    kmemoryView(QWidget *parent);

    /**
     * Destructor
     */
    virtual ~kmemoryView();
    
public slots:
    void cardSelected(CardItem* cardData);
    void setRowSize(int itemsPerRow);
    
private:
    CardItem* m_last;
    QList<CardItem*> m_cards;
    
    QSizeF m_cardsSize;
};

#endif // kmemoryVIEW_H
