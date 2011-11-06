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

#include "themesmodel.h"
#include "themeiconsprovider.h"
#include "pairstheme.h"
#include <KStandardDirs>
#include <KGlobal>
#include <QDebug>
#include <QFileSystemWatcher>

ThemesModel::ThemesModel(QObject* parent): QStandardItemModel(parent)
{
    reload();
    
    QStringList themesdirs=KGlobal::dirs()->findDirs("appdata", "themes");
    QFileSystemWatcher* fs=new QFileSystemWatcher(this);
    fs->addPaths(themesdirs);
    connect(fs, SIGNAL(directoryChanged(QString)), SLOT(reload()));
}

void ThemesModel::reload()
{
    clear();
    const QStringList themes = KGlobal::dirs()->findAllResources("appdata", QLatin1String( "themes/*.pairs.*" ));

    Q_FOREACH(const QString& themePath, themes) {
        PairsTheme* theme = new PairsTheme(themePath);

        if(!theme->isCorrect()) {
            qWarning() << "uncorrect theme:" << themePath << theme->error();
            delete theme;
        } else {
            appendRow(theme);
        }
    }
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

QVariant ThemesModel::info(int row, const QByteArray& role)
{
    QHash<int, QByteArray> roles=roleNames();
    return QStandardItemModel::data(index(row, 0), roles.key(role));
}

QHash< int, QByteArray> ThemesModel::roleNames() const
{
    QHash<int, QByteArray> names=QStandardItemModel::roleNames();
    names.insert(PairsTheme::CardTypeRole, "type");
    names.insert(PairsTheme::LanguagesRole, "languages");
    return names;
}
