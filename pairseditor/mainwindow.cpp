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

#include "mainwindow.h"
#include "mainwindowview.h"
#include "thememodel.h"
#include "ui_mainwindowview.h"
#include "elementitem.h"
#include <KFileDialog>
#include <KMessageBox>
#include <QtCore/QDebug>
#include <QtCore/QProcess>
#include <KAction>
#include <KGlobal>
#include <KStandardDirs>
#include <KStandardAction>
#include <kdeversion.h>
#include <KUrlRequester>
#include <KTar>
#include <KActionCollection>

MainWindow::MainWindow(QWidget *parent) : KXmlGuiWindow(parent)
{

    m_selectedItem = 0;
    m_pt = 0;
    m_model = 0;
    m_tmpDir = 0;
    m_process = 0;
    m_fileSaved = true;
    setMinimumSize (900, 400);
    m_mainWidget = new MainWindowView(this);
    connect(m_mainWidget, SIGNAL(changed()), this, SLOT(doChange()));
    setCentralWidget(m_mainWidget);
    KStandardAction::openNew(this, SLOT(doNew()), actionCollection());
    KStandardAction::open(this, SLOT(doOpen()), actionCollection());
    KStandardAction::save(this, SLOT(doSave()), actionCollection());
    KStandardAction::saveAs(this, SLOT(doSaveAs()), actionCollection());
    KAction *myact = new KAction(KIcon("pairs"), i18n("Try"), this);
    connect(myact, SIGNAL(triggered(bool)), this, SLOT(doTry()));
    actionCollection()->addAction("try", myact);
    KStandardAction::quit(this, SLOT(close()), actionCollection());
    m_mainWidget->widgetsHide();
    createGUI();
    actionCollection()->action("help_whats_this");

    doNew();
}

MainWindow::~MainWindow()
{
}

bool MainWindow::askToSave()
{
    if (!m_fileSaved)
    {
    	switch ( KMessageBox::warningYesNoCancel( this, i18n("Save changes to the document?")) ) {
    		case KMessageBox::Yes :
    			doSave();
    			return true;
    		case KMessageBox::No :
    	         return true;
    		default: // cancel
    			return false;
    	}
    }
    return true;
}

bool MainWindow::queryClose()
{
    return askToSave();
}


void MainWindow::doTry()
{
    if (!m_fileSaved)
    {
    	doSave();
    }
    if(m_file.isEmpty())
    {
    	return;
    }
    qDebug() << "try" << m_file ;
    m_process = new QProcess(this);
    m_process->start("pairs " + m_file);
    connect(m_process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(pairsFinished()));
}

void MainWindow::pairsFinished()
{
    qDebug() << "Pairs Finished";
//    QFile::remove(m_pairsFile);
    delete m_process;
}

void MainWindow::doSaveAs()
{
    m_file.clear();
    doSave();
}

void MainWindow::doNew()
{
	if(m_model && !askToSave())
		return;
    m_file.clear();
    delete m_model;
    newTmpDir(QDir::tempPath() + "/newfile");
    m_model = new ThemeModel(this);
    m_mainWidget->setModel(m_model);
    m_mainWidget->clearUi(m_tmpDir->path());
    m_mainWidget->widgetsHide();
    m_fileSaved = true;
}

void MainWindow::doSave()
{
    if(!m_mainWidget->check())
    {
        qDebug() << "Check not passed:";
        qDebug() << m_mainWidget->checkString();
        KMessageBox::error(this, m_mainWidget->checkString(), i18n("File not saved"));
        return ;
    }

    if(m_file.isEmpty())
    {
        m_file = KFileDialog::getSaveFileName(KUrl(QDir::currentPath()), "*.pairs.tar.bz2|" + i18n("Pairs Themes"), this, i18n("Save Pairs theme"));
        QFileInfo fi(m_file);
        m_gameFile = m_tmpDir->absolutePath() + '/' + fi.baseName() + ".game";
        if(m_file.isEmpty())
            return;
    }
    qDebug() << m_file << m_gameFile;

    QFile f(m_gameFile);
    if (!f.open(QFile::WriteOnly | QFile::Text))
    {
            qWarning() << "Error: Cannot write file " << m_file;
            return;
    }

    QXmlStreamWriter stream(&f);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("pairs");
    stream.writeAttribute("xmlns", "http://edu.kde.org/game");
    m_mainWidget->writeXmlCommon(&stream);
    for (int i=0; i < m_model->rowCount(); i++)
    {
        ElementItem *myitem = static_cast<ElementItem*> (m_model->item(i,0));
        myitem->writeElement(&stream);
    }
    stream.writeEndElement(); // pairs
    stream.writeEndDocument();
    f.close();

    compress(m_file);
    m_fileSaved = true;
    setCaption(m_mainWidget->title(), !m_fileSaved);
}


void MainWindow::openfile(const QString& filename)
{
    delete m_pt;
    m_pt = new PairsThemeEditor(filename);
    m_model = new ThemeModel(*m_pt, this);
    m_mainWidget->setModel(m_model);
    m_mainWidget->setUi(m_pt);
    m_mainWidget->widgetsHide();
    m_fileSaved = true;
    setCaption(m_mainWidget->title(), !m_fileSaved);

}

void MainWindow::doOpen()
{
	if(!askToSave())
		return;
    m_file = KFileDialog::getOpenFileName(KUrl(QDir::currentPath()), "*.pairs.tar.bz2|" + i18n("Pairs Themes"), this, i18n("Open Pairs theme"));
    if(!m_file.isEmpty())
    {
        QFileInfo pathInfo(m_file);
        extract(m_file);
        QStringList flist = m_tmpDir->entryList(QStringList("*.game"), QDir::Files | QDir::NoSymLinks);
        Q_ASSERT(!flist.isEmpty());
        m_gameFile = m_tmpDir->absolutePath() + '/' + flist.front();
        openfile(m_gameFile);
    }
}

QString MainWindow::copyFile(KUrlRequester *k)
{
    QString newFile = m_tmpDir->path() + '/' + k->url().fileName();
    qDebug() << "file "<< newFile << k->text();
    if(newFile != k->text())
        QFile::copy(k->url().path(), newFile);
    return newFile;
}

void MainWindow::extract(QString path)
{
    KTar archive(path);
    newTmpDir(QDir::tempPath() + '/' + QFileInfo(path).fileName());
    const bool opened = archive.open(QIODevice::ReadOnly);
    Q_ASSERT(opened);
    QStringList files(archive.directory()->entries());
    Q_FOREACH(const QString filename, files)
    {
        Q_ASSERT(archive.directory()->entry(filename)->isFile());
        const KArchiveFile* file = static_cast<const KArchiveFile*>(archive.directory()->entry(filename));
        file->copyTo(m_tmpDir->path());
    }
    archive.close();
}

void MainWindow::compress(QString path)
{
    KTar archive(path);
    const bool opened = archive.open(QIODevice::WriteOnly);
    Q_ASSERT(opened);
    archive.addLocalDirectory(m_tmpDir->path(), "");
    archive.close();
    m_tmpDir->rmpath(m_tmpDir->path());
}

void MainWindow::newTmpDir(const QString &path)
{
    delete m_tmpDir;
    m_tmpDir = new QDir(path);
    while(m_tmpDir->exists())
        m_tmpDir->setPath(m_tmpDir->path()+'a');
    m_tmpDir->mkpath(m_tmpDir->path());

}

void MainWindow::doChange()
{
    m_fileSaved = false;
    setCaption(m_mainWidget->title(), !m_fileSaved);
}
