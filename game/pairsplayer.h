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

#ifndef KPAIRSPLAYER_H
#define KPAIRSPLAYER_H

#include <QString>
#include <QStandardItem>

class PairsPlayer : public QStandardItem
{
public:
    PairsPlayer(const QString &name, const QString &icon);
    ~PairsPlayer(){}
    void reset();
    void incMissed();
    void incFound();
    void incSeconds();
    int missed() const {return m_missed; }
    int found() const {return m_found; }
    int seconds() const {return m_seconds; }
    QString name() const {return m_name; }
    QString icon() const {return m_icon; }
    void setSelected(bool s);
    bool isSelected() const;

private:
    QString m_name;
    QString m_icon;
    int m_missed;
    int m_found;
    int m_seconds;
};

#endif
