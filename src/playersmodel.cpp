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

PlayersModel::PlayersModel(QObject* parent): QStandardItemModel(parent)
{
    KConfig config;
    KConfigGroup group(&config, "NewGame");
    QStringList players = group.readEntry("Players", QStringList() << i18n("Player"));
    QStringList icons = group.readEntry("Icons", QStringList() << i18n("get-hot-new-stuff"));
    PairsPlayer *player;
    foreach(const QString& name, players) {
        int ind = players.indexOf(name, 0);
        const QString icon = icons.at(ind);
        player = new PairsPlayer(name, icon);
        appendRow(player);
    }

/*    QStringList themesdirs=KGlobal::dirs()->findDirs("appdata", "themes");
    QFileSystemWatcher* fs=new QFileSystemWatcher(this);
    fs->addPaths(themesdirs);
    connect(fs, SIGNAL(directoryChanged(QString)), SLOT(reload()));
    */
}

/*
void PlayersModel::reload()
{
    clear();
    const QStringList themes = KGlobal::dirs()->findAllResources("appdata", QLatin1String( "themes/*.pairs.*" ));

    Q_FOREACH(const QString& themePath, themes) {
        PairsTheme* theme = new PairsTheme(themePath);

        if(!theme->isCorrect()) {
            qWarning() << "uncorrect theme:" << themePath << theme->error();
            delete theme;
        } else {
            appendRow(theme);
            if(m_themeicons != 0)
                m_themeicons->addTheme(theme->title(), theme);
        }
    }
}
*/

QVariant PlayersModel::info(int row, const QByteArray& role)
{
    QHash<int, QByteArray> roles=roleNames();
    return QStandardItemModel::data(index(row, 0), roles.key(role));
}

QHash< int, QByteArray> PlayersModel::roleNames() const
{
    QHash<int, QByteArray> names=QStandardItemModel::roleNames();
    names.insert(PairsPlayer::Missed, "missed");
    names.insert(PairsPlayer::Found, "found");
    names.insert(PairsPlayer::Time, "time");
    return names;
}
