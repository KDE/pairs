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
#include <QtCore/QCoreApplication>

#include <kconfigdialog.h>
#include <kstatusbar.h>

#include <kaction.h>
#include <KToolBar>
#include <kactioncollection.h>
#include <kstandardaction.h>

#include <KDE/KLocale>
#include "newmemorydialog.h"

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
    
    QMetaObject::invokeMethod(this, "newGame", Qt::QueuedConnection);
}

kmemory::~kmemory()
{
}

void kmemory::setupActions()
{
    KStandardAction::open(this, SLOT(newGame()), actionCollection());
    KStandardAction::quit(qApp, SLOT(closeAllWindows()), actionCollection());
}

void kmemory::newGame()
{
    NewMemoryDialog dialog;
    
    if(dialog.exec()==QDialog::Accepted) {
        m_view->newGame(dialog.theme(), dialog.rows(), dialog.columns());
    }
}

#include "kmemory.moc"
