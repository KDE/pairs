/*  This file is part of Pairs
 *
 *  Copyright (C) <2012>       <Aleix Pol>           <aleixpol@kde.org>
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KXmlGuiWindow>
#include <QtCore/QModelIndex>

class QItemSelection;
class PairsThemeEditor;
class QDir;
class QStandardItem;
class ThemeModel;
class KUrlRequester;
class QProcess;
class MainWindowView;

class MainWindow : public KXmlGuiWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void openfile(const QString& path);
    
public slots:
    void doNew();
    void doOpen();
    void doSave();
    void doSaveAs();
    void doTry();
    void pairsFinished();
    QString copyFile(KUrlRequester *k);
    void doChange() {m_fileSaved = false;}

protected:
    virtual bool queryClose();

private:
    MainWindowView *m_mainWidget;
    PairsThemeEditor *m_pt;
    QStandardItem *m_selectedItem;
    ThemeModel *m_model;
    QString m_file;
    QString m_gameFile;
    QString m_pairsFile;
    QDir *m_tmpDir;
    QProcess *m_process;
    bool m_fileSaved;

    void newTmpDir(const QString &path);
    void extract(QString path);
    void compress(QString path);
    bool askToSave();

};

#endif // MAINWINDOW_H
