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

#ifndef PAIRS_H
#define PAIRS_H


#include <KMainWindow>
#include <QTimer>
#include <QList>
#include <pairsplayer.h>

namespace Phonon { class MediaObject; }
class PairsView;
class KToggleAction;

class Pairs : public KMainWindow
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    Pairs();

    /**
     * Default Destructor
     */
    virtual ~Pairs();
    void Play(QIODevice * ioDevice);
    PairsView* view() const { return m_view; }
    
    virtual QSize sizeHint() const { return QSize(800,500); }
    
public slots:
    void inc_missed();
    void inc_found();

private slots:
    void newGame();

private:
    PairsView *m_view;
    Phonon::MediaObject *m_media;
    QString m_right;
    QString m_wrong;
};

#endif // PAIRS_H
