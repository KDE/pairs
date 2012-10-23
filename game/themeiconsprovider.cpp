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

#include "themeiconsprovider.h"
#include <QPainter>
#include <QSvgRenderer>
#include "themesmodel.h"
#include <QDebug>
#include <QFile>
#include <KStandardDirs>



ThemeIconsProvider::ThemeIconsProvider(QDeclarativeImageProvider::ImageType type, ThemesModel* themes) :
    QDeclarativeImageProvider(type), m_themes(themes)
{}

ThemeIconsProvider::~ThemeIconsProvider()
{}

QPixmap ThemeIconsProvider::requestPixmap(const QString& id, QSize* size, const QSize& requestedSize)
{
    QByteArray data = m_themes->themeData(id);
    if(data.isNull()) {
        QString dir = KGlobal::dirs()->findResourceDir("appdata", QLatin1String( "gameicons/pairs.svg"));
        QFile f(dir+"gameicons/pairsIcon.svg");
        f.open(QIODevice::ReadOnly);
        data = f.readAll();
    }
    QSvgRenderer pixRenderer(data);
    if(size) {
        *size = pixRenderer.viewBox().size();
    }
    QPixmap px(requestedSize.isValid() && !requestedSize.isEmpty() ? requestedSize : pixRenderer.viewBox().size());
    px.fill(Qt::transparent);
    QPainter p(&px);
    pixRenderer.render(&p);
    return px;
}
