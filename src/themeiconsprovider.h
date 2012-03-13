/*
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

#ifndef THEMEICONSPROVIDER_H_
#define THEMEICONSPROVIDER_H_

#include <QDeclarativeImageProvider>
#include "pairstheme.h"

class ThemesModel;
class ThemeIconsProvider : public QDeclarativeImageProvider
{
    public:
        ThemeIconsProvider(QDeclarativeImageProvider::ImageType type, ThemesModel* themes);
        ~ThemeIconsProvider();
        QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requestedSize);

	private:
        ThemesModel* m_themes;
};


#endif /* THEMEICONSPROVIDER_H_ */
