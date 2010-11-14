/*
 * kmemoryview.h
 *
 * Copyright (C) 2007 Albert Astals Cid <aacid@kde.org>
 */

#ifndef KMEMORYVIEW_H
#define KMEMORYVIEW_H

#include <QtGui/QGraphicsView>

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
};

#endif // kmemoryVIEW_H
