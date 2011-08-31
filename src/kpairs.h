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

#ifndef KMEMORY_H
#define KMEMORY_H


#include <kxmlguiwindow.h>
#include <QTimer>
#include <QTime>

class kpairsView;
class KToggleAction;

class kpairs : public KXmlGuiWindow
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    kpairs();

    /**
     * Default Destructor
     */
    virtual ~kpairs();
public slots:
    void inc_missed();
    void inc_found();
    void update();

private slots:
    void newGame();
    
private:
    void setupActions();
    void setScore();

private:
    kpairsView *m_view;

    int m_missed;
    int m_found;
    KToggleAction *m_toolbarAction;
    KToggleAction *m_statusbarAction;
    QTimer *m_timer;
    QTime *m_gameduration;
};

#endif // _KMEMORY_H_
