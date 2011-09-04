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
#include <QList>
#include <QListWidget>
#include <QPushButton>
#include <QDebug>

#include "ui_newpairsdialog.h"
#include "pairstheme.h"


NewMemoryDialog::NewMemoryDialog(QWidget* parent)
    : QDialog(parent)
    , m_ui(new Ui::NewMemoryDialog)
{
	m_ui->setupUi(this);
	QPushButton *addButton = new QPushButton(tr("&Add"));
	addButton->setDefault(true);

    QPushButton *delButton = new QPushButton(tr("&Delete"));
	addButton->setDefault(true);

	m_ui->playerButtons->clear();
	m_ui->playerButtons->addButton(addButton, QDialogButtonBox::ActionRole);
	m_ui->playerButtons->addButton(delButton, QDialogButtonBox::ActionRole);
	connect(addButton, SIGNAL(clicked()), this, SLOT(add_user()));
	connect(delButton, SIGNAL(clicked()), this, SLOT(del_user()));
    
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

const QStringList NewMemoryDialog::players()
{
	QStringList result;
	for (int i = 0; i < m_ui->playerList->count(); i++)
	{
		result << m_ui->playerList->item(i)->text();
	}
	if(result.isEmpty())
	{
		result << "Player";
	}
	return result;
}

void NewMemoryDialog::setPlayer(const QString &name)
{
	m_ui->playerList->addItem(name);
}

void NewMemoryDialog::add_user()
{
	m_ui->playerList->addItem(m_ui->playerName->toPlainText());
	m_ui->playerName->clear();
}

void NewMemoryDialog::del_user()
{
	delete m_ui->playerList->item(0);
}
