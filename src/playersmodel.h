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

#ifndef PLAYERSMODEL_H
#define PLAYERSMODEL_H

#include <QStandardItemModel>

class ThemesModel;
class PairsPlayer;
class PlayersModel : public QStandardItemModel
{
    Q_OBJECT
    public:
        enum PlayerRoles {
            Missed = Qt::UserRole + 1,
            Found,
            Time
        };
        
        explicit PlayersModel(QObject* parent);
        virtual ~PlayersModel();
        
        PairsPlayer* player(int row);
        Q_SCRIPTABLE void addPlayer(const QString& player, const QString& decoration);
        Q_SCRIPTABLE void removePlayers();
        void resetPlayers();
        
    public slots:
        QVariant info(int row, const QByteArray& role);
        void setSelected(int row);
        QString randomIcon();
        void gameStarted();
        void newGame();
        QString iconsDir(){return m_gameicons;};

    
    private:
        void refresh();
        QStringList m_playerIcons;
        QString m_gameicons;
};


#endif // PLAYERSMODEL_H
