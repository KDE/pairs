/*
 * kmemory.cpp
 *
 * Copyright (C) 2008 Albert Astals Cid <aacid@kde.org>
 */
#include "kmemory.h"
#include "kmemoryview.h"
#include "settings.h"

#include <QtGui/QDropEvent>
#include <QtGui/QPainter>
#include <QtGui/QPrinter>

#include <kconfigdialog.h>
#include <kstatusbar.h>

#include <kaction.h>
#include <KToolBar>
#include <kactioncollection.h>
#include <kstandardaction.h>

#include <KDE/KLocale>

kmemory::kmemory()
    : KXmlGuiWindow(),
      m_view(new kmemoryView(this))
{
    // accept dnd
    setAcceptDrops(true);

    // tell the KXmlGuiWindow that this is indeed the main widget
    setCentralWidget(m_view);

    // then, setup our actions
    setupActions();

    // add a status bar
    statusBar()->show();

    // a call to KXmlGuiWindow::setupGUI() populates the GUI
    // with actions, using KXMLGUI.
    // It also applies the saved mainwindow settings, if any, and ask the
    // mainwindow to automatically save settings if changed: window size,
    // toolbar position, icon size, etc.
    setupGUI();
    
    QSpinBox* itemsPerRowInput = new QSpinBox(this);
    itemsPerRowInput->setMinimum(0);
    itemsPerRowInput->setValue(5);
    connect(itemsPerRowInput, SIGNAL(valueChanged(int)), m_view, SLOT(setRowSize(int)));
    
    toolBar()->addWidget(itemsPerRowInput);
}

kmemory::~kmemory()
{
}

void kmemory::setupActions()
{
    KStandardAction::quit(qApp, SLOT(closeAllWindows()), actionCollection());
}

#include "kmemory.moc"
