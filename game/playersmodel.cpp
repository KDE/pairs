/*  This file is part of Pairs
 *
 *  Copyright (C) <2011>       <Aleix Pol>           <aleixpol@kde.org>
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

#include "playersmodel.h"
#include "pairsplayer.h"
#include <KStandardDirs>
#include <KConfig>
#include <KConfigGroup>
#include <KLocalizedString>
#include <KGlobal>
#include <krandom.h>
#include <QDebug>
#include <QFileSystemWatcher>
#include "themesmodel.h"

PlayersModel::PlayersModel(QObject* parent)
    : QStandardItemModel(parent)
{
    QHash<int, QByteArray> names=QStandardItemModel::roleNames();
    names.insert(Missed, "missed");
    names.insert(Found, "found");
    names.insert(Time, "time");
    names.insert(Selected, "selected");
    setRoleNames(names);
    m_playerIcons = KGlobal::dirs()->findAllResources("appdata", QLatin1String( "players/*.svg"));
    for(QStringList::iterator it=m_playerIcons.begin(), itEnd=m_playerIcons.end(); it!=itEnd; ++it) {
        *it = QUrl::fromLocalFile(*it).toString();
    }

    QMetaObject::invokeMethod(this, "refresh", Qt::QueuedConnection);
}

PlayersModel::~PlayersModel()
{
    QStringList players, icons;
    
    for (int i = 0; i < rowCount(); ++i) {
        PairsPlayer* p=player(i);
        players += p->text();
        icons += p->data(Qt::DecorationRole).toString();
    }
    
    KConfig config;
    KConfigGroup group(&config, "NewGame");
    group.writeEntry("Players", players);
    group.writeEntry("Icons", icons);
}

bool PlayersModel::isAnySelected()
{
    for (int i = 0; i < rowCount(); ++i) {
        if(player(i)->isSelected())
            return true;
    }
    return false;
}


void PlayersModel::refresh()
{
    KConfig config;
    KConfigGroup group(&config, "NewGame");
    QStringList players = group.readEntry("Players", QStringList() << i18n("Player"));
    QStringList icons = group.readEntry("Icons", QStringList() << QString());

    int i=0;
    foreach(const QString& name, players) {
        QString icon = icons[i];
        if(!m_playerIcons.contains(icon))
            icon = randomIcon();
        
        addPlayer(name, icon);
        i++;
    }
}

PairsPlayer* PlayersModel::player(int row)
{
    return static_cast<PairsPlayer*>(item(row));
}

QString PlayersModel::randomIcon()
{
    int row = KRandom::random() % m_playerIcons.count();
    return m_playerIcons[row];
}

QVariant PlayersModel::info(int row, const QByteArray& role)
{
    QHash<int, QByteArray> roles=roleNames();
    return QStandardItemModel::data(index(row, 0), roles.key(role));
}

void PlayersModel::addPlayer(const QString& name, const QString& decoration)
{
    appendRow(new PairsPlayer(name, decoration));
}

void PlayersModel::toggleSelection(int row)
{
     PairsPlayer* p=player(row);
     p->setSelected(!p->isSelected());
}

void PlayersModel::resetPlayers()
{
    for (int i = 0; i < rowCount(); ++i) {
         player(i)->reset();
    }
}

void PlayersModel::removePlayer(int p)
{
    invisibleRootItem()->removeRow(p);
}

QUrl PlayersModel::iconsDir(const QString& path)
{
    return QUrl::fromLocalFile(QStandardPaths::locate(QStandardPaths::DataLocation, path));
}
