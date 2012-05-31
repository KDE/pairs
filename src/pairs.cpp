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

#include "pairs.h"
#include "pairsview.h"

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
#include <KApplication>

#include "playersmodel.h"
#include <kstatusbar.h>

Pairs::Pairs()
    : KMainWindow()
    , m_view(new PairsView(this))
{
    setWindowIcon(KIcon("pairs"));
    setWindowTitle(qAppName());
    setCentralWidget(m_view);
    
    setAutoSaveSettings();
}

Pairs::~Pairs()
{}

#include "pairs.moc"
