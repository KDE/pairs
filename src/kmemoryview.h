/*
 * kmemoryview.h
 *
 * Copyright (C) 2007 Albert Astals Cid <aacid@kde.org>
 */
#ifndef KMEMORYVIEW_H
#define KMEMORYVIEW_H

#include <QtGui/QWidget>

#include "ui_kmemoryview_base.h"

class QPainter;
class KUrl;

/**
 * This is the main view class for kmemory.  Most of the non-menu,
 * non-toolbar, and non-statusbar (e.g., non frame) GUI code should go
 * here.
 *
 * @short Main view
 * @author Albert Astals Cid <aacid@kde.org>
 * @version 0.1
 */

class kmemoryView : public QWidget, public Ui::kmemoryview_base
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

private:
    Ui::kmemoryview_base ui_kmemoryview_base;

signals:
    /**
     * Use this signal to change the content of the statusbar
     */
    void signalChangeStatusbar(const QString& text);

    /**
     * Use this signal to change the content of the caption
     */
    void signalChangeCaption(const QString& text);

private slots:
    void switchColors();
    void settingsChanged();
};

#endif // kmemoryVIEW_H
