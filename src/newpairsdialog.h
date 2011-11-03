/*
 *  Copyright (C) <2010>       <Aleix Pol>           <aleixpol@kde.org>
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

#ifndef NEWPairsDialog_H
#define NEWPairsDialog_H

#include <kdialog.h>
#include <QListWidgetItem>
#include "pairstheme.h"

class ThemesModel;
namespace Ui { class NewPairsDialog; }

class NewPairsDialog
    : public QDialog
{
    Q_OBJECT
    public:
        explicit NewPairsDialog(QWidget* parent = 0);
        PairsTheme* theme() const;
        QStringList players();
        void setPlayer(const QString &name);
        QString language() const;
        QString cardType() const;

    public slots:
        void addUser();
        void addUser(const QString& name);
        void deleteUser();
        void playerNameChanged(const QString & newname);
        void themeSelected(const QModelIndex& idx);
        void dialogAccepted();

    private slots:
        void download();

    private:
        Ui::NewPairsDialog* m_ui;
		ThemesModel* m_themesModel;
        QList<PairsTheme> m_themes;
};

#endif // NEWPairsDialog_H
