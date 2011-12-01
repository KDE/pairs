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
