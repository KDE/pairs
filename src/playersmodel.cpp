/* This file is part of Pairs
    Copyright 2011 Aleix Pol Gonzalez <aleixpol@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "playersmodel.h"
#include "pairsplayer.h"
#include <KStandardDirs>
#include <KConfig>
#include <KConfigGroup>
#include <KLocalizedString>
#include <KGlobal>
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
    m_playerIcons = KGlobal::dirs()->findAllResources("appdata", QLatin1String( "players/*.png"));

    refresh();
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
    int row = qrand() % m_playerIcons.count();
    QString result = "file://" + m_playerIcons[row];
    return result;
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

QString PlayersModel::iconsDir(const QString& path)
{
    return "file://"+KGlobal::dirs()->findResource("appdata", path);
}
