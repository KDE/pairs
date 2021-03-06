/*  This file is part of Pairs
 *
 *  Copyright (C) <2008>       <Albert Astals Cid>   <aacid@kde.org>
 *  Copyright (C) <2010>       <Aleix Pol>           <aleixpol@kde.org>
 *  Copyright (C) <2011>       <Marco Calignano>     <marco.calignano@googlemail.com>
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
    Pairs(const QString &file = "");

    /**
     * Default Destructor
     */
    virtual ~Pairs();
    PairsView* view() const { return m_view; }
    
    virtual QSize sizeHint() const { return QSize(800,500); }
    
private:
    PairsView *m_view;
    QString m_right;
    QString m_wrong;
};

#endif // PAIRS_H
