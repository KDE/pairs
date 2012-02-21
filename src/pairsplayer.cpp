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

#include "pairsplayer.h"
#include "KIcon"
#include "playersmodel.h"

PairsPlayer::PairsPlayer(const QString &name, const QString &icon)
    : QStandardItem(name),
    m_name(name),
    m_icon(icon)
{
    reset();
    setText(name);
    setData(m_missed, PlayersModel::Missed);
    setData(m_found, PlayersModel::Found);
    setData(m_seconds, PlayersModel::Time);
    setData(m_icon, Qt::DecorationRole);
    setSelected(true);
}

void PairsPlayer::reset()
{
    m_found = 0;
    m_missed = 0;
    m_seconds = 0;
}

void PairsPlayer::incFound()
{
    m_found++;
    setData(m_found, PlayersModel::Found);
}

void PairsPlayer::incMissed()
{
    m_missed++;
    setData(m_missed, PlayersModel::Missed);
}

void PairsPlayer::incSeconds()
{
    m_seconds++;
    setData(m_seconds, PlayersModel::Time);
}

void PairsPlayer::setSelected(bool s)
{
    setData(s, PlayersModel::Selected);
}

bool PairsPlayer::isSelected() const
{
    return data(PlayersModel::Selected).toBool();
}
