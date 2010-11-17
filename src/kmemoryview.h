/*
 * kmemoryview.h
 *
 * Copyright (C) 2007 Albert Astals Cid <aacid@kde.org>
 */

#ifndef KMEMORYVIEW_H
#define KMEMORYVIEW_H

#include <QtGui/QGraphicsView>

class MemoryTheme;
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
    
    void setRowSize(int itemsPerRow);
    void newGame(const MemoryTheme& theme, int rows, int columns);
public slots:
    void cardSelected(CardItem* cardData);
    
private:
    CardItem* m_last;
    QList<CardItem*> m_cards;
    
    QSizeF m_cardsSize;
};

#endif // kmemoryVIEW_H
