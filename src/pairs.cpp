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
#include "playersmodel.h"

Pairs::Pairs()
    : KXmlGuiWindow()
    , m_view(new PairsView(this))
	, m_right(KGlobal::dirs()->findResource("appdata", "themes/right.ogg"))
	, m_wrong(KGlobal::dirs()->findResource("appdata", "themes/wrong.ogg"))

{
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
    
//     QMetaObject::invokeMethod(this, "newGame", Qt::QueuedConnection);
}

Pairs::~Pairs()
{}

void Pairs::setupActions()
{
    KStandardAction::open(this, SLOT(newGame()), actionCollection());
    KAction *theme = new KAction("Get new theme", actionCollection());
    theme->setIcon(KIcon("get-hot-new-stuff"));
    actionCollection()->addAction("theme", theme);
    connect(theme, SIGNAL(triggered(bool)), m_view, SLOT(download()));


    KStandardAction::quit(qApp, SLOT(closeAllWindows()), actionCollection());
}

void Pairs::newGame()
{
    NewPairsDialog dialog;

    statusBar()->showMessage(i18n("New Game"));
    if(dialog.exec()!=QDialog::Accepted) {
        return;
    }

    m_view->playersModel()->clear();
    for(int i= 0; i < dialog.players().count(); i++)
    {
        m_view->playersModel()->addPlayer(dialog.players().at(i), "get-hot-new-stuff");
    }
    m_view->newGame(dialog.theme(), dialog.language(), dialog.cardType());

    m_view->playersModel()->resetPlayers();
    
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
}

void Pairs::inc_found()
{
    if(m_media->state()==Phonon::PlayingState) {
        m_media->setQueue(QList<Phonon::MediaSource>() << m_right);
    } else {
        m_media->setCurrentSource(m_right);
        m_media->play();
    }
}

#include "pairs.moc"
