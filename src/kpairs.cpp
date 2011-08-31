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
#include <KMessageBox>
#include <kactioncollection.h>
#include <kstandardaction.h>

#include <KDE/KLocale>
#include "newpairsdialog.h"

kpairs::kpairs()
    : KXmlGuiWindow()
    , m_view(new kpairsView(this))
    , m_missed(0)
    , m_found(0)
{
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
                
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

void kpairs::update()
{
//    qDebug() << "update";
    setScore();
}

void kpairs::newGame()
{
    NewMemoryDialog dialog;

    statusBar()->showMessage(i18n("New Game"));
    if(dialog.exec()==QDialog::Accepted) {
        m_view->newGame(dialog.theme(), dialog.rows(), dialog.columns());
    }
    m_missed = 0;
    m_found = 0;
    m_gameduration.start();
    m_timer->start(1000);
    statusBar()->showMessage(i18n("New Game started"));
}

void kpairs::inc_missed()
{
   m_missed++;
   setScore();
}

void kpairs::inc_found()
{
   m_found++;
   setScore();
}

void kpairs::setScore()
{
   int dur=m_gameduration.elapsed()/1000;
   QTime dd(0,0, dur);
   QString line = i18n("Duration %1 - pairs missed: %2 pairs found: %3", dd.toString("mm:ss"), m_missed, m_found);
   statusBar()->showMessage(line);
   if(m_found == m_view->cardsNum()/2)
   {
       m_timer->stop();
       KMessageBox::information	(this, i18n("Congratulations you finished the game\n%1", line), i18n("Congratulations"));
   }
}

#include "kpairs.moc"
