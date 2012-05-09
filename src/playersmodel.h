/* This file is part of Pairs
    Copyright 2011 Aleix Pol Gonzalez <aleixpol@kde.org>
    Copyright 2011 Marco Calignano    <marco.calignano@googlemail.com>
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

#ifndef PLAYERSMODEL_H
#define PLAYERSMODEL_H

#include <QStandardItemModel>
#include <QUrl>

class ThemesModel;
class PairsPlayer;
class PlayersModel : public QStandardItemModel
{
    Q_OBJECT
    public:
        enum PlayerRoles {
            Missed = Qt::UserRole + 1,
            Found,
            Time,
            Selected
        };
        
        explicit PlayersModel(QObject* parent);
        virtual ~PlayersModel();
        
        PairsPlayer* player(int row);
        Q_SCRIPTABLE void addPlayer(const QString& player, const QString& decoration);
        Q_SCRIPTABLE void removePlayer(int index);
        void resetPlayers();
        
    public slots:
        QVariant info(int row, const QByteArray& role);
        void toggleSelection(int row);
        QString randomIcon();
        QUrl iconsDir(const QString& path);
        bool isAnySelected();

    private slots:
        void refresh();
        
    private:
        QStringList m_playerIcons;
};


#endif // PLAYERSMODEL_H
