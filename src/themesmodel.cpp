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

#include "themesmodel.h"
#include "themeiconsprovider.h"
#include "pairstheme.h"
#include <KStandardDirs>
#include <KGlobal>
#include <krandom.h>
#include <QDebug>


ThemesModel::ThemesModel(QObject* parent): QStandardItemModel(parent)
{
    QHash<int, QByteArray> names=QStandardItemModel::roleNames();
    names.insert(PairsTheme::CardTypeRole, "type");
    names.insert(PairsTheme::LanguagesRole, "languages");
    setRoleNames(names);
    
    QStringList themesdirs=KGlobal::dirs()->findDirs("appdata", "themes");
    m_fs=new QFileSystemWatcher(this);
    m_fs->addPaths(themesdirs);
    connect(m_fs, SIGNAL(directoryChanged(QString)), SLOT(reload()));
    
    QMetaObject::invokeMethod(this, "reload", Qt::QueuedConnection);
}

void ThemesModel::reload()
{
    m_fs->blockSignals(true);
    clear();
    const QStringList themes = KGlobal::dirs()->findAllResources("appdata", QLatin1String( "themes/*.pairs.*" ));

    Q_FOREACH(const QString& themePath, themes) {
        PairsTheme* theme = new PairsTheme(themePath);

        if(!theme->isCorrect()) {
            qWarning() << "Incorrect theme:" << themePath << theme->error();
            delete theme;
        } else {
        	int iNumber = 0;
        	while(nameExists(theme->title())) {
        		iNumber++;
        		theme->setTitle(theme->title() + "(" + QString::number(iNumber) + ")" );
			}  // namespace )
        	qDebug()<< theme->title();
            appendRow(theme);
        }
    }
    m_fs->blockSignals(false);
}

PairsTheme* ThemesModel::themeForName(const QString& title) const
{
    PairsTheme* ret=0;
    for(int i=0; !ret && i<rowCount(); ++i) {
        PairsTheme* theme=static_cast<PairsTheme*>(item(i, 0));
        if(theme->title()==title)
            ret=theme;
    }
    return ret;
}

bool ThemesModel::nameExists(const QString& title) const
{
    for(int i=0; i<rowCount(); ++i) {
        PairsTheme* theme=static_cast<PairsTheme*>(item(i, 0));
        if(theme->title()==title)
            return true;
    }
    return false;
}

QVariant ThemesModel::info(int row, const QByteArray& role)
{
    QHash<int, QByteArray> roles=roleNames();
    return QStandardItemModel::data(index(row, 0), roles.key(role));
}

bool ThemesModel::isPertinent(int row, const QString& type, const QString& lang)
{
    PairsTheme* theme=static_cast<PairsTheme*>(item(row, 0));
    return theme->isPertinent(type, lang);
}

QString ThemesModel::randomThemesImage() const
{
    int row = KRandom::random() % rowCount();
    PairsTheme* t = static_cast<PairsTheme*>(item(row, 0));
    QStringList imgs = t->images();
    
    return QString("image://theme/%1/%2").arg(t->title()).arg(imgs[qrand() % imgs.size()]);
}

bool ThemesModel::exists(const QString& id)
{
    int firstSlash = id.indexOf('/');
    
    const PairsTheme *theme = 0;
    if(firstSlash>=0)
        theme = themeForName(id.left(firstSlash));
    
    if(!theme)
        return false;

    QString path = id.right(id.size()-firstSlash-1);
    return theme && theme->hasFile(path);
}

QByteArray ThemesModel::themeData(const QString& id) const
{
    int firstSlash = id.indexOf('/');
    
    const PairsTheme *theme = 0;
    if(firstSlash>=0)
        theme = themeForName(id.left(firstSlash));
    
    if(!theme)
        return QByteArray();

    QString path = id.right(id.size()-firstSlash-1);
    return theme->themeData(path);
}
