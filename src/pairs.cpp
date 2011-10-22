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

#include "pairs.h"
#include "pairsview.h"
#include "settings.h"

#include <QtGui/QDropEvent>
#include <QtGui/QPainter>
#include <QtGui/QPrinter>
#include <QtCore/QCoreApplication>
#include <QList>

#include <kconfigdialog.h>
#include <kstatusbar.h>

#include <kaction.h>
#include <KToolBar>
#include <KMessageBox>
#include <kactioncollection.h>
#include <kstandardaction.h>
#include <kstandarddirs.h>
#include <KDE/KLocale>

#include <Phonon/MediaObject>
#include <Phonon/AudioOutput>
#include "newpairsdialog.h"

Pairs::Pairs()
    : KXmlGuiWindow()
    , m_view(new PairsView(this))
    , m_players()
    , m_found(0)
	, m_right(KGlobal::dirs()->findResource("appdata", "themes/right.ogg"))
	, m_wrong(KGlobal::dirs()->findResource("appdata", "themes/wrong.ogg"))

{
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_media = new Phonon::MediaObject(this);
    Phonon::AudioOutput *audioOutput = new Phonon::AudioOutput(Phonon::GameCategory, this);
    createPath(m_media, audioOutput);

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

Pairs::~Pairs()
{
}

void Pairs::setupActions()
{
    KStandardAction::open(this, SLOT(newGame()), actionCollection());
    KStandardAction::quit(qApp, SLOT(closeAllWindows()), actionCollection());
}

void Pairs::update()
{
//    qDebug() << "update";
	m_players[m_currentplayer].incSeconds();
    setScore();
}

void Pairs::newGame()
{
    NewPairsDialog dialog;

    statusBar()->showMessage(i18n("New Game"));
    if(dialog.exec()==QDialog::Accepted) {
    	m_players.clear();
    	for(int i= 0; i < dialog.players().count(); i++)
    	{
    		m_players.append(PairsPlayer(dialog.players().at(i)));
    	}
    	m_view->newGame(dialog.theme(), dialog.language(), dialog.cardType());
    }

/*
	QString myname("player1");
	m_players.append(pairsPlayer(myname));
	myname = "player2";
	m_players.append(pairsPlayer(myname));
*/

    m_found = 0;
    for (int i = 0; i < m_players.size(); ++i) {
         m_players[i].reset();
    }
    m_currentplayer = 0;
    m_timer->start(1000);
    statusBar()->showMessage(i18n("New Game started"));
}

void Pairs::inc_missed()
{
    if(m_media->state()==Phonon::PlayingState) {
        m_media->setQueue(QList<Phonon::MediaSource>() << m_wrong);
    } else {
        m_media->setCurrentSource(m_wrong);
        m_media->play();
    }
    
	m_players[m_currentplayer].incMissed();
	++m_currentplayer %= m_players.size();
	setScore();
}

void Pairs::inc_found()
{
    if(m_media->state()==Phonon::PlayingState) {
        m_media->setQueue(QList<Phonon::MediaSource>() << m_right);
    } else {
        m_media->setCurrentSource(m_right);
        m_media->play();
    }
    
    m_found++;
    m_players[m_currentplayer].incFound();
    setScore();
}

void Pairs::setScore()
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

#include "pairs.moc"
