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

#include "themeiconsprovider.h"
#include <KTar>
#include <QPainter>
#include <QSvgRenderer>
#include "themesmodel.h"
#include <QDebug>


ThemeIconsProvider::ThemeIconsProvider(QDeclarativeImageProvider::ImageType type, ThemesModel* themes) :
    QDeclarativeImageProvider(type), m_themes(themes)
{}

ThemeIconsProvider::~ThemeIconsProvider()
{}

QPixmap ThemeIconsProvider::requestPixmap(const QString& id, QSize* size, const QSize& requestedSize)
{
    int firstSlash = id.indexOf('/');
    
    const PairsTheme *theme = 0;
    if(firstSlash>=0)
        theme = m_themes->themeForName(id.left(firstSlash));
    
    if(theme){
        QString path = id.right(id.size()-firstSlash-1);
        KTar archive(theme->path());
        bool b = archive.open(QIODevice::ReadOnly);
        Q_ASSERT(b);
        QSvgRenderer pixRenderer(static_cast<const KArchiveFile*>(archive.directory()->entry(path))->data());
        if(size) {
            *size = pixRenderer.viewBox().size();
        }
        QPixmap px(requestedSize.isValid() ? requestedSize : pixRenderer.viewBox().size());
        px.fill(Qt::transparent);
        QPainter p(&px);
        pixRenderer.render(&p);
        return px;
    }

    return QPixmap();
}
