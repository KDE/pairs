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
    , m_players()
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
	m_players[m_currentplayer].incSeconds();
    setScore();
}

void kpairs::newGame()
{
    NewMemoryDialog dialog;

    for(int y = 0; y< m_players.count(); y++)
    {
    	dialog.setPlayer(m_players[y].name());
    }
    statusBar()->showMessage(i18n("New Game"));
    if(dialog.exec()==QDialog::Accepted) {
    	m_players.clear();
    	for(int i= 0; i < dialog.players().count(); i++)
    	{
    		m_players.append(KPairsPlayer(dialog.players().at(i)));
    	}
    	m_view->newGame(dialog.theme());
    }

/*
	QString myname("player1");
	m_players.append(KPairsPlayer(myname));
	myname = "player2";
	m_players.append(KPairsPlayer(myname));
*/

    m_found = 0;
    for (int i = 0; i < m_players.size(); ++i) {
         m_players[i].reset();
    }
    m_currentplayer = 0;
    m_timer->start(1000);
    statusBar()->showMessage(i18n("New Game started"));
}

void kpairs::inc_missed()
{
	m_players[m_currentplayer].incMissed();
	++m_currentplayer %= m_players.size();
	setScore();
}

void kpairs::inc_found()
{
   m_found++;
   m_players[m_currentplayer].incFound();
   setScore();
}

void kpairs::setScore()
{
    QTime dd(0,0, m_players[m_currentplayer].seconds());
    QString line = i18n("%1: Duration %2 - pairs missed: %3 pairs found: %4",
            m_players[m_currentplayer].name(),
            dd.toString("mm:ss"),
            m_players[m_currentplayer].missed(),
            m_players[m_currentplayer].found()
   );
   statusBar()->showMessage(line);
   if(m_found == m_view->cardsNum()/2 && m_view->cardsNum() != 0)
   {
        m_timer->stop();
        QString final_line (i18n("Congratulations you finished the game\n"));
        for(int i = 0; i < m_players.size(); ++i)
        {
            dd.setHMS(0,0,0);

            final_line += i18n("%1: Duration %2 - pairs missed: %3 pairs found: %4\n",
                            m_players[i].name(),
                            dd.addSecs(m_players[i].seconds()).toString("mm:ss"),
                            m_players[i].missed(),
                            m_players[i].found()
                            );
        }
        KMessageBox::information(this, final_line, i18n("Congratulations"));
   }
}

#include "kpairs.moc"
