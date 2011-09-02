/*
 *  Copyright (C) <2010>       <Aleix Pol>           <aleixpol@kde.org>
 *  Copyright (C) <2011>       <Marco Calignano>     <marco.calignano@gmail.com>
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

#include "newpairsdialog.h"
#include <KLocalizedString>
#include <KStandardDirs>
#include <QBoxLayout>
#include <QListWidget>
#include <QDebug>

#include "ui_newpairsdialog.h"
#include "pairstheme.h"

NewMemoryDialog::NewMemoryDialog(QWidget* parent)
    : QDialog(parent)
    , m_ui(new Ui::NewMemoryDialog)
{
    m_ui->setupUi(this);
    
    const QStringList themes = KGlobal::dirs()->findAllResources("appdata", QLatin1String( "themes/*.pairs.*" ));
    foreach(const QString& themePath, themes) {
        MemoryTheme theme(themePath);
        
        if(!theme.isCorrect()) {
            qWarning() << "uncorrect theme:" << themePath << theme.error();
        } else {
            m_ui->themesList->addItem(theme.name());
            m_themes += theme;
        }
    }
    m_ui->themesList->setCurrentItem(m_ui->themesList->item(0));
}

MemoryTheme NewMemoryDialog::theme() const
{
    int row = m_ui->themesList->currentRow();
    return m_themes.at(row);
}
