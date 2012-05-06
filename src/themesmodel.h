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

#ifndef THEMESMODEL_H
#define THEMESMODEL_H

#include <QStandardItemModel>

class PairsTheme;
class ThemesModel : public QStandardItemModel
{
    Q_OBJECT
    public:
        explicit ThemesModel(QObject* parent = 0);

        PairsTheme* themeForName(const QString& title) const;
        bool exists(const QString& icon);
        QByteArray themeData(const QString& path) const;
        
    public slots:
        QVariant info(int row, const QByteArray& role);
        bool isPertinent(int row, const QString &type,const QString &lang);
        
        /** @returns a random image from any theme */
        QString randomThemesImage() const;
        
    private slots:
        void reload();
};

#endif // THEMESMODEL_H
