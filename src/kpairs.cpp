/*
 *  Copyright (C) <2008>       <Albert Astals Cid>   <aacid@kde.org>
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

#include "kpairs.h"
#include "kpairsview.h"
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
#include "newpairsdialog.h"

kpairs::kpairs()
    : KXmlGuiWindow(),
      m_view(new kpairsView(this))
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

kpairs::~kpairs()
{
}

void kpairs::setupActions()
{
    KStandardAction::open(this, SLOT(newGame()), actionCollection());
    KStandardAction::quit(qApp, SLOT(closeAllWindows()), actionCollection());
}

void kpairs::newGame()
{
    NewMemoryDialog dialog;
    
    if(dialog.exec()==QDialog::Accepted) {
        m_view->newGame(dialog.theme(), dialog.rows(), dialog.columns());
    }
}

#include "kpairs.moc"
