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
#include "pairs.h"
#include "pairstheme.h"
#include <KApplication>


NewPairsDialog::NewPairsDialog(QWidget* parent)
    : QDialog(parent)
    , m_ui(new Ui::NewPairsDialog)
{
	m_ui->setupUi(this);
    m_ui->add->setIcon(KIcon("list-add"));
    m_ui->remove->setIcon(KIcon("list-remove"));
    connect(m_ui->add, SIGNAL(clicked()), this, SLOT(addUser()));
    connect(m_ui->remove, SIGNAL(clicked()), this, SLOT(deleteUser()));
    connect(m_ui->playerName, SIGNAL(textChanged(QString)), SLOT(playerNameChanged(QString)));
    connect(m_ui->themesList, SIGNAL(itemClicked(QListWidgetItem *)), SLOT(themeSelected(QListWidgetItem *)));
	connect(this, SIGNAL(accepted()), SLOT(dialogAccepted()));
    connect(m_ui->theme, SIGNAL(clicked(bool)), SLOT(download()));
    m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    loadThemesList();

	KConfig config;
	KConfigGroup group(&config, "NewGame");
	QStringList players = group.readEntry("Players", QStringList() << i18n("Player"));

	foreach(const QString& name, players) {
		addUser(name);
	}
}

void NewPairsDialog::download(){
    Pairs *anch = static_cast<Pairs*> (this->parent());
    anch->download();
    m_ui->themesList->clear();
    loadThemesList();
}

void NewPairsDialog::loadThemesList(){
    const QStringList themes = KGlobal::dirs()->findAllResources("appdata", QLatin1String( "themes/*.pairs.*" ));
    
    Q_FOREACH(const QString& themePath, themes) {
        PairsTheme theme(themePath);
        
        if(!theme.isCorrect()) {
            qWarning() << "uncorrect theme:" << themePath << theme.error();
        } else {
            m_ui->themesList->addItem(theme.title());
            m_themes += theme;
        }
    }
    m_ui->playerName->setClickMessage(i18n("Player name..."));
    m_ui->themesList->setCurrentRow(0);
    themeSelected(m_ui->themesList->currentItem());


}

PairsTheme NewPairsDialog::theme() const
{
    int row = m_ui->themesList->currentRow();
    return m_themes[row];
}
QString NewPairsDialog::language() const
{
    return m_ui->comboLanguages->currentText();
//    m_ui->comboCardTypes->clear();
//    m_ui->comboCardTypes->addItems(m_themes[m_row].cardTypes()[m_ui->comboLanguages->currentText()]);
}

QString NewPairsDialog::cardType() const
{
    return m_ui->comboCardTypes->currentText();
}

void NewPairsDialog::themeSelected(QListWidgetItem *item)
{
	m_row = m_ui->themesList->row(item);
    m_ui->comboLanguages->clear();
	m_ui->comboCardTypes->clear();
	
	m_ui->comboLanguages->addItems(m_themes[m_row].languages());
//	m_ui->comboCardTypes->addItems(m_themes[m_row].cardTypes()[m_ui->comboLanguages->currentText()]);
}

QStringList NewPairsDialog::players()
{
	QStringList result;
	for (int i = 0; i < m_ui->playerList->count(); i++)
	{
		result << m_ui->playerList->item(i)->text();
	}
	
	return result;
}

void NewPairsDialog::setPlayer(const QString &name)
{
	m_ui->playerList->addItem(name);
    bool hasUsers = m_ui->playerList->count() > 0;
    m_ui->remove->setEnabled(hasUsers);
    m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(hasUsers);

}

void NewPairsDialog::addUser()
{
	addUser(m_ui->playerName->text());
}

void NewPairsDialog::addUser(const QString& name)
{
	m_ui->playerList->addItem(name);
    m_ui->playerList->setCurrentRow(m_ui->playerList->count()-1);
	m_ui->playerName->clear();
    
    m_ui->add->setEnabled(false);
    m_ui->remove->setEnabled(true);
    m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

void NewPairsDialog::deleteUser()
{
    qDeleteAll(m_ui->playerList->selectedItems());
    
    bool hasUsers = m_ui->playerList->count()>0;
    m_ui->remove->setEnabled(hasUsers);
    m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(hasUsers);
}

void NewPairsDialog::playerNameChanged(const QString & newname)
{
    m_ui->add->setEnabled(!newname.isEmpty());
}

void NewPairsDialog::dialogAccepted()
{
	KConfig config;
	KConfigGroup group(&config, "NewGame");
	group.writeEntry("Players", players());
}
