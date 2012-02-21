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
#include <QtCore/QCoreApplication>
#include <QList>

#include <kconfigdialog.h>

#include <kaction.h>
#include <KToolBar>
#include <KMessageBox>
#include <kactioncollection.h>
#include <kstandardaction.h>
#include <kstandarddirs.h>
#include <KDE/KLocale>

#include <Phonon/MediaObject>
#include <Phonon/AudioOutput>
#include "playersmodel.h"
#include <kstatusbar.h>

Pairs::Pairs()
    : KMainWindow()
    , m_view(new PairsView(this))
    , m_right(KGlobal::dirs()->findResource("appdata", "themes/right.ogg"))
    , m_wrong(KGlobal::dirs()->findResource("appdata", "themes/wrong.ogg"))

{
    m_media = new Phonon::MediaObject(this);
    Phonon::AudioOutput *audioOutput = new Phonon::AudioOutput(Phonon::GameCategory, this);
    createPath(m_media, audioOutput);
    
    setCentralWidget(m_view);
}

Pairs::~Pairs()
{}

void Pairs::inc_missed(const QString& wrong)
{
    playSound(wrong.isEmpty() ? m_wrong : wrong);
}

void Pairs::inc_found(const QString& found)
{
    qDebug() << "playing" << found;
    playSound(found.isEmpty() ? m_right : found);
}

void Pairs::playSound(const QString& sound) const
{
    if(m_media->state()==Phonon::PlayingState) {
        m_media->setQueue(QList<Phonon::MediaSource>() << sound);
    } else {
        m_media->setCurrentSource(sound);
        m_media->play();
    }
}

#include "pairs.moc"
