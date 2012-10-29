/*  This file is part of Pairs
 *
 *  Copyright (C) <2012>       <Heena Mahour>        <heena393@gmail.com>
 *  Copyright (C) <2012>       <Marco Calignano>     <marco.calignano@gmail.com>
 *
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

#ifndef MAINWINDOWVIEW_H
#define MAINWINDOWVIEW_H

#include <QtGui/QWidget>
#include <QtCore/QModelIndex>
#include <QtGui/QItemSelection>

class QXmlStreamWriter;
class PairsThemeEditor;
class ThemeModel;
class QStandardItem;
class MainWindow;

namespace Phonon {
class MediaObject;
}
namespace Ui {
class MainWindowView;
}

class MainWindowView : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWindowView(QWidget *parent = 0);
    ~MainWindowView();
    void widgetsHide();
    void clearUi(const QString &path);
    void writeXmlCommon(QXmlStreamWriter *stream);
    Ui::MainWindowView *ui(){return m_ui;};
    void setUi(PairsThemeEditor *theme);
    void setModel(ThemeModel *model);
    bool check();
    QString checkString() const {return m_checkMessage;};

signals:
	void changed();

public slots:
    void elementSelected(const QModelIndex & item);
    void backSelected();
    void fileSelected();
    void selectionChanged(const QItemSelection& selected, const QItemSelection&);
    void wordChanged(const QString &word);
    void addElement();
    void deleteElement();
    void addFeature(int index);
    void playSound();

private:
    MainWindow *m_parent;
    Ui::MainWindowView *m_ui;
    QString m_checkMessage;
    QString m_path;
    ThemeModel *m_model;
    PairsThemeEditor *m_pt;
    QStandardItem *m_selectedItem;
    QPixmap scaleImage(const QPixmap &i, int max) const;
    Phonon::MediaObject *m_media;
};

#endif // MAINWINDOWVIEW_H
