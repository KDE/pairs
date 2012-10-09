#include "mainwindow.h"
#include "pairstheme.h"
#include "thememodel.h"
#include "elementitem.h"
#include "featureitem.h"
#include "ui_mainwindow.h"
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QtCore/QProcess>
#include <KAction>
#include <KGlobal>
#include <KStandardDirs>
#include <KStandardAction>
#include <kdeversion.h>
#include <KUrlRequester>
#include <KTar>

MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),
    m_ui(new Ui::MainWindow)

{
    m_pt = 0;
    m_model = 0;
    m_tmpDir = 0;
    m_process = 0;
    m_ui->setupUi(this);
    KAction *myact = KStandardAction::create(KStandardAction::New, this, SLOT(doNew()), m_ui->menu_file);
    m_ui->menu_file->addAction(myact);
    m_ui->toolBar->addAction(myact);
    myact = KStandardAction::create(KStandardAction::Open, this, SLOT(doOpen()), m_ui->menu_file);
    m_ui->menu_file->addAction(myact);
    m_ui->toolBar->addAction(myact);
    myact = KStandardAction::create(KStandardAction::Save, this, SLOT(doSave()), m_ui->menu_file);
    m_ui->menu_file->addAction(myact);
    m_ui->toolBar->addAction(myact);
    myact = KStandardAction::create(KStandardAction::SaveAs, this, SLOT(doSaveAs()), m_ui->menu_file);
    m_ui->menu_file->addAction(myact);
    m_ui->toolBar->addAction(myact);
    myact = new KAction(KIcon("go-up"), i18n("Upload"), m_ui->menu_file);
    connect(myact, SIGNAL(triggered(bool)), this, SLOT(doUpload()));
//    ui->menu_file->addAction(myact);
//    ui->toolBar->addAction(myact);
    myact = new KAction(KIcon("pairs"), i18n("Try"), m_ui->menu_file);
    connect(myact, SIGNAL(triggered(bool)), this, SLOT(doTry()));
    m_ui->menu_file->addAction(myact);
    m_ui->toolBar->addAction(myact);
    widgetsHide();
    connect(m_ui->fileKurl, SIGNAL(urlSelected(KUrl)), this, SLOT(fileSelected()));
    connect(m_ui->backKurl, SIGNAL(urlSelected(KUrl)), this, SLOT(backSelected()));
    connect(m_ui->wordEdit, SIGNAL(textChanged(QString)), this, SLOT(wordChanged(QString)));
    connect(m_ui->delButton, SIGNAL(clicked()), this, SLOT(deleteElement()));
    connect(m_ui->addButton, SIGNAL(clicked()), this, SLOT(addElement()));
    connect(m_ui->moreButton, SIGNAL(currentIndexChanged(int)), this, SLOT(addFeature(int)));
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::widgetsHide()
{
    m_ui->imageLabel->hide();
    m_ui->fileKurl->hide();
    m_ui->wordEdit->hide();
    m_ui->wordLabel->hide();
    m_ui->langLabel->hide();
    m_ui->comboBox_2->hide();
    m_ui->moreButton->hide();
    m_ui->itemLabel->hide();
}

bool MainWindow::check()
{
    m_checkMessage.clear();
    if(m_ui->titleEdit->text().isEmpty())
    {
        m_checkMessage = i18n("The Title is missing");
        return false;
    }
    if(m_ui->authorEdit->text().isEmpty())
    {
        m_checkMessage = i18n("The Author is missing");
        return false;
    }
    if(m_ui->versionEdit->text().isEmpty())
    {
        m_checkMessage = i18n("The Version is missing");
        return false;
    }
    if(m_ui->descriptionEdit->text().isEmpty())
    {
        m_checkMessage = i18n("The Description is missing");
        return false;
    }
    if(m_ui->backKurl->text().isEmpty())
    {
        m_checkMessage = i18n("The Back Image is missing");
        return false;
    }
    for (int i=0; i < m_model->rowCount(); i++)
    {
        ElementItem *myitem = static_cast<ElementItem*> (m_model->item(i,0));
        if(!myitem->check(i+1))
        {
            m_checkMessage =  myitem->checkMessage();
            return false;
        }
    }
    return true;
}

void MainWindow::addFeature(int index)
{
    QStandardItem *paren = m_selectedItem;
    if(m_selectedItem->data(ThemeModel::CardTypeRole).toInt())
        paren = m_selectedItem->parent();
    qDebug() << "addFeature called" << index;
    CardType newType;
    switch(index)
    {
        case 0:
        default:
            newType = CARD_IMAGE;
            break;
        case 1:
            newType = CARD_LOGIC;
            break;
        case 2:
            newType = CARD_SOUND;
            break;
        case 3:
            newType = CARD_WORD;
            break;
    }
    FeatureItem *fi = new FeatureItem(newType, "any", "");
    m_model->insertFeature(fi, paren);


}

void MainWindow::addElement()
{
    if(m_selectedItem->data(ThemeModel::CardTypeRole).toInt())
        return;
    const ThemeElement el;
    ElementItem *newItem = new ElementItem (el);
    QString name = i18n("Element %1", m_model->rowCount()+1);
    newItem->setText(name);
    m_model->insertItem(newItem);
}

void MainWindow::deleteElement()
{
    m_model->removeItem(m_selectedItem);
}

void MainWindow::doUpload()
{

}

void MainWindow::doTry()
{
    doSave();
    KStandardDirs tmp;
    QString dir = tmp.findDirs("data", "pairs").first() + "themes/";
    QFileInfo pathInfo(m_file);
    m_pairsFile = dir + pathInfo.fileName();
    qDebug() << "try" << m_pairsFile << m_file ;
    QFile::copy(m_file, m_pairsFile);
    QProcess *m_process = new QProcess(this);
    m_process->start("pairs");
    connect(m_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(pairsFinished()));
}

void MainWindow::pairsFinished()
{
    qDebug() << "Pairs Finished";
    QFile::remove(m_pairsFile);
    delete m_process;
}

void MainWindow::doSaveAs()
{
    m_file.clear();
    doSave();
}

void MainWindow::doNew()
{
    m_file.clear();
    delete m_model;
    newTmpDir(QDir::tempPath() + "/newfile");
    m_model = new ThemeModel(this);
    m_ui->treeView->setModel(m_model);
    m_ui->titleEdit->setText("");
    m_ui->authorEdit->setText("");
    m_ui->versionEdit->setText("");
    m_ui->dateEdit->setDate(QDate::currentDate());
    m_ui->maintypeBox->setCurrentIndex(0);
    m_ui->descriptionEdit->setText("");
    m_ui->backKurl->setText("");
    m_ui->pixLabel->setPixmap(QPixmap());
    m_ui->fileKurl->setStartDir(KUrl(QDir::currentPath()));
    m_ui->backKurl->setStartDir(KUrl(QDir::currentPath()));
    widgetsHide();
    m_ui->splitter->setStretchFactor(1, 3);
    connect(m_ui->treeView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), SLOT(selectionChanged(QItemSelection,QItemSelection)));

}

void MainWindow::doSave()
{
    if(!check())
    {
        qDebug() << "Check not passed:";
        qDebug() << m_checkMessage;
        QMessageBox(QMessageBox::Critical, "File not saved", m_checkMessage, QMessageBox::Ok, this).exec();
        return ;
    }

    if(m_file.isEmpty())
    {
        m_file = QFileDialog::getSaveFileName(this, tr("Save Pairs theme"), QDir::currentPath(), tr("Pairs Themes (*.pairs.tar.bz2)"));
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
    stream.writeTextElement("title", m_ui->titleEdit->text());
    stream.writeTextElement("description", m_ui->descriptionEdit->text());
    stream.writeTextElement("author", m_ui->authorEdit->text());
    stream.writeTextElement("date", m_ui->dateEdit->text());
    stream.writeTextElement("version", m_ui->versionEdit->text());
    stream.writeStartElement("image");
    stream.writeAttribute("type", "back");
    stream.writeAttribute("src", m_ui->backKurl->text());
    stream.writeEndElement(); // image
    stream.writeStartElement("main");
    QString maintype = m_ui->maintypeBox->currentText();
    if(maintype == "relation")
        maintype = "image";
    stream.writeAttribute("type", maintype);
    stream.writeEndElement(); // main
    for (int i=0; i < m_model->rowCount(); i++)
    {
        ElementItem *myitem = static_cast<ElementItem*> (m_model->item(i,0));
        myitem->writeElement(&stream);
    }
    stream.writeEndElement(); // pairs
    stream.writeEndDocument();
    f.close();

    compress(m_file);
}


void MainWindow::open(const QString& filename)
{
//    m_file = filename;
    delete m_pt;
    m_pt = new PairsTheme(filename);
    m_model = new ThemeModel(*m_pt, this);
    m_ui->treeView->setModel(m_model);
    m_ui->titleEdit->setText(m_pt->title());
    m_ui->authorEdit->setText(m_pt->author());
    m_ui->versionEdit->setText(m_pt->version());
    m_ui->dateEdit->setDate(QDate::fromString(m_pt->date(),"d/M/yyyy"));
    m_ui->maintypeBox->setCurrentIndex(m_pt->mainType()-1);
    m_ui->descriptionEdit->setText(m_pt->description());
    m_ui->backKurl->setText(m_pt->backImage());
    QPixmap image(m_pt->path()+"/"+m_pt->backImage());
    m_ui->pixLabel->setPixmap(image.scaledToWidth(100));
    m_ui->fileKurl->setStartDir(KUrl(m_pt->path()));
    m_ui->backKurl->setStartDir(KUrl(m_pt->path()));
    widgetsHide();
    m_ui->splitter->setStretchFactor(1, 3);
    connect(m_ui->treeView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), SLOT(selectionChanged(QItemSelection,QItemSelection)));
    
}

void MainWindow::doOpen()
{
    m_file = QFileDialog::getOpenFileName(this, tr("Open Pairs theme"), QDir::currentPath(), tr("Pairs Themes (*.pairs.tar.bz2)"));
    if(!m_file.isEmpty())
    {
        QFileInfo pathInfo(m_file);
        extract(m_file);
        QStringList flist = m_tmpDir->entryList(QStringList("*.game"), QDir::Files | QDir::NoSymLinks);
        Q_ASSERT(!flist.isEmpty());
        m_gameFile = m_tmpDir->absolutePath() + "/" + flist.front();
        open(m_gameFile);
    }
}

void MainWindow::selectionChanged(const QItemSelection& selected, const QItemSelection&  )
{
    if(!selected.isEmpty())
        elementSelected(selected.indexes().first());
}

void MainWindow::elementSelected(const QModelIndex & idx)
{
    m_selectedItem = m_model->itemFromIndex(idx);
    int type = idx.data(ThemeModel::CardTypeRole).toInt();
    m_ui->fileKurl->setText(idx.data(ThemeModel::PathRole).toString());
    m_ui->wordEdit->setText(idx.data(ThemeModel::PathRole).toString());
    int index = m_ui->comboBox_2->findText(idx.data(ThemeModel::LanguageRole).toString());
    if ( index != -1 )
    {
        m_ui->comboBox_2->setCurrentIndex(index);
    }
    else
    {
        m_ui->comboBox_2->addItem(idx.data(ThemeModel::LanguageRole).toString());
    }
    m_ui->moreButton->show();
    qDebug() << "card Type" << type;
    if(!type)
    {
        widgetsHide();
        return;
    }
    m_ui->langLabel->show();
    m_ui->comboBox_2->show();
    QPixmap image;
    switch(type)
    {
    case CARD_IMAGE:
        widgetsHide();
        m_ui->imageLabel->setText("Image file");
        m_ui->imageLabel->show();
        m_ui->itemLabel->show();
        m_ui->fileKurl->show();
        image.load(m_pt->path()+"/"+m_ui->fileKurl->text());
        m_ui->itemLabel->setPixmap(image.scaledToWidth(100));
        break;
    case CARD_SOUND:
    case CARD_SOUNDLOGIC:
        widgetsHide();
        m_ui->imageLabel->setText("Sound file");
        m_ui->imageLabel->show();
        m_ui->fileKurl->show();
        break;
    case CARD_LOGIC:
        widgetsHide();
        m_ui->imageLabel->setText("Logic image file");
        m_ui->itemLabel->show();
        m_ui->imageLabel->show();
        m_ui->fileKurl->show();
        image.load(m_pt->path()+"/"+m_ui->fileKurl->text());
        m_ui->itemLabel->setPixmap(image.scaledToWidth(100));
        break;
    case CARD_WORD:
        widgetsHide();
        m_ui->wordEdit->show();
        m_ui->wordLabel->show();
        break;
    case CARD_FOUND:
        widgetsHide();
        m_ui->imageLabel->setText("Found sound file");
        m_ui->imageLabel->show();
        m_ui->fileKurl->show();
        break;

    }
}
void MainWindow::backSelected()
{
    QPixmap image;
    QString newFile = copyFile(m_ui->backKurl);
    m_ui->backKurl->setText(m_ui->backKurl->url().fileName());
    image.load(newFile);
    m_ui->pixLabel->setPixmap(image.scaledToWidth(100));
}
void MainWindow::fileSelected()
{
    QPixmap image;
    QString newFile = copyFile(m_ui->fileKurl);
    m_ui->fileKurl->setText(m_ui->fileKurl->url().fileName());
    image.load(newFile);
    m_ui->itemLabel->setPixmap(image.scaledToWidth(100));
    m_selectedItem->setData(m_ui->fileKurl->text(),ThemeModel::PathRole);
    m_selectedItem->setText(m_ui->fileKurl->text());

}

void MainWindow::wordChanged(const QString &word)
{
    m_selectedItem->setData(word, ThemeModel::PathRole);
    m_selectedItem->setText(word);
}

QString MainWindow::copyFile(KUrlRequester *k)
{
    QString newFile = m_tmpDir->path() + "/" + k->url().fileName();
    qDebug() << "file "<< newFile << k->text();
    if(newFile != k->text())
        QFile::copy(k->url().path(), newFile);
    return newFile;
}

void MainWindow::extract(QString path)
{
    KTar archive(path);
    newTmpDir(QDir::tempPath() + "/" + QFileInfo(path).fileName());
    Q_ASSERT(archive.open(QIODevice::ReadOnly));
    QStringList files(archive.directory()->entries());
    Q_FOREACH(QString filename, files)
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
    Q_ASSERT(archive.open(QIODevice::WriteOnly));
    archive.addLocalDirectory(m_tmpDir->path(), "");
    archive.close();
    m_tmpDir->rmpath(m_tmpDir->path());
}

void MainWindow::newTmpDir(const QString &path)
{
    delete m_tmpDir;
    m_tmpDir = new QDir(path);
    while(m_tmpDir->exists())
        m_tmpDir->setPath(m_tmpDir->path()+"a");
    m_tmpDir->mkpath(m_tmpDir->path());

}
