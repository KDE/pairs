/*
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

class PairsPlayer
{

public:
    PairsPlayer(const QString &name);
    ~PairsPlayer(){};
    void reset();
    void incMissed() {m_missed++; };
    void incFound() {m_found++; };
    void incSeconds() {m_seconds++; };
    int missed() {return m_missed; };
    int found() {return m_found; };
    int seconds() {return m_seconds; };
    const QString &name() {return m_name; };

private:
    QString m_name;
    int m_missed;
    int m_found;
    int m_seconds;

};

#endif
