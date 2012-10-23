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
