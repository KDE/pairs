#include "mainwindow.h"
#include "pairstheme.h"
#include "thememodel.h"
#include "elementitem.h"
#include "featureitem.h"
#include "ui_mainwindowview.h"
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
#include <KActionCollection>
#include <KAboutData>

MainWindow::MainWindow(QWidget *parent) : KXmlGuiWindow(parent)
{

    m_selectedItem = 0;
    m_pt = 0;
    m_model = 0;
    m_tmpDir = 0;
    m_process = 0;
    KAboutData aboutData( "ptedit", "ptedit3", ki18n("PTEdit"), "1.0",
                          ki18n("Editor for pairs thems"), KAboutData::License_GPL,
                          ki18n("Copyright (c) 2012 Marco Calignano") );
    setMinimumSize (900, 400);
    m_mainWidget = new MainWindowView(this);
    setCentralWidget(m_mainWidget);
    KAction *myact = KStandardAction::create(KStandardAction::New, this, SLOT(doNew()), this);
    actionCollection()->addAction("new", myact);
    myact = KStandardAction::create(KStandardAction::Open, this, SLOT(doOpen()), this);
    actionCollection()->addAction("open", myact);
    myact = KStandardAction::create(KStandardAction::Save, this, SLOT(doSave()), this);
    actionCollection()->addAction("save", myact);
    myact = KStandardAction::create(KStandardAction::SaveAs, this, SLOT(doSaveAs()), this);
    actionCollection()->addAction("saveas", myact);
//    myact = new KAction(KIcon("go-up"), i18n("Upload"), this);
//    actionCollection()->addAction("new", myact);
//    connect(myact, SIGNAL(triggered(bool)), this, SLOT(doUpload()));
//    ui->menu_file->addAction(myact);
//    ui->toolBar->addAction(myact);
    myact = new KAction(KIcon("pairs"), i18n("Try"), this);
    connect(myact, SIGNAL(triggered(bool)), this, SLOT(doTry()));
    actionCollection()->addAction("try", myact);
    m_mainWidget->widgetsHide();
    createGUI();
    connect(m_mainWidget->ui()->fileKurl, SIGNAL(urlSelected(KUrl)), this, SLOT(fileSelected()));
    connect(m_mainWidget->ui()->backKurl, SIGNAL(urlSelected(KUrl)), this, SLOT(backSelected()));
    connect(m_mainWidget->ui()->wordEdit, SIGNAL(textChanged(QString)), this, SLOT(wordChanged(QString)));
    connect(m_mainWidget->ui()->delButton, SIGNAL(clicked()), this, SLOT(deleteElement()));
    connect(m_mainWidget->ui()->addButton, SIGNAL(clicked()), this, SLOT(addElement()));
    connect(m_mainWidget->ui()->moreButton, SIGNAL(currentIndexChanged(int)), this, SLOT(addFeature(int)));
}

MainWindow::~MainWindow()
{
}

bool MainWindow::check()
{
    m_checkMessage.clear();
    if(m_mainWidget->ui()->titleEdit->text().isEmpty())
    {
        m_checkMessage = i18n("The Title is missing");
        return false;
    }
    if(m_mainWidget->ui()->authorEdit->text().isEmpty())
    {
        m_checkMessage = i18n("The Author is missing");
        return false;
    }
    if(m_mainWidget->ui()->versionEdit->text().isEmpty())
    {
        m_checkMessage = i18n("The Version is missing");
        return false;
    }
    if(m_mainWidget->ui()->descriptionEdit->text().isEmpty())
    {
        m_checkMessage = i18n("The Description is missing");
        return false;
    }
    if(m_mainWidget->ui()->backKurl->text().isEmpty())
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
    m_mainWidget->ui()->treeView->setModel(m_model);
    m_mainWidget->ui()->titleEdit->setText("");
    m_mainWidget->ui()->authorEdit->setText("");
    m_mainWidget->ui()->versionEdit->setText("");
    m_mainWidget->ui()->dateEdit->setDate(QDate::currentDate());
    m_mainWidget->ui()->maintypeBox->setCurrentIndex(0);
    m_mainWidget->ui()->descriptionEdit->setText("");
    m_mainWidget->ui()->backKurl->setText("");
    m_mainWidget->ui()->pixLabel->setPixmap(QPixmap());
    m_mainWidget->ui()->fileKurl->setStartDir(KUrl(QDir::currentPath()));
    m_mainWidget->ui()->backKurl->setStartDir(KUrl(QDir::currentPath()));
    m_mainWidget->widgetsHide();
    m_mainWidget->ui()->splitter->setStretchFactor(1, 3);
    connect(m_mainWidget->ui()->treeView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), SLOT(selectionChanged(QItemSelection,QItemSelection)));

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
    stream.writeTextElement("title", m_mainWidget->ui()->titleEdit->text());
    stream.writeTextElement("description", m_mainWidget->ui()->descriptionEdit->text());
    stream.writeTextElement("author", m_mainWidget->ui()->authorEdit->text());
    stream.writeTextElement("date", m_mainWidget->ui()->dateEdit->text());
    stream.writeTextElement("version", m_mainWidget->ui()->versionEdit->text());
    stream.writeStartElement("image");
    stream.writeAttribute("type", "back");
    stream.writeAttribute("src", m_mainWidget->ui()->backKurl->text());
    stream.writeEndElement(); // image
    stream.writeStartElement("main");
    QString maintype = m_mainWidget->ui()->maintypeBox->currentText();
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
    m_mainWidget->ui()->treeView->setModel(m_model);
    m_mainWidget->ui()->titleEdit->setText(m_pt->title());
    m_mainWidget->ui()->authorEdit->setText(m_pt->author());
    m_mainWidget->ui()->versionEdit->setText(m_pt->version());
    m_mainWidget->ui()->dateEdit->setDate(QDate::fromString(m_pt->date(),"d/M/yyyy"));
    m_mainWidget->ui()->maintypeBox->setCurrentIndex(m_pt->mainType()-1);
    m_mainWidget->ui()->descriptionEdit->setText(m_pt->description());
    m_mainWidget->ui()->backKurl->setText(m_pt->backImage());
    QPixmap image(m_pt->path()+"/"+m_pt->backImage());
    m_mainWidget->ui()->pixLabel->setPixmap(image.scaledToWidth(100));
    m_mainWidget->ui()->fileKurl->setStartDir(KUrl(m_pt->path()));
    m_mainWidget->ui()->backKurl->setStartDir(KUrl(m_pt->path()));
    m_mainWidget->widgetsHide();
    m_mainWidget->ui()->splitter->setStretchFactor(1, 3);
    connect(m_mainWidget->ui()->treeView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), SLOT(selectionChanged(QItemSelection,QItemSelection)));
    
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
    m_mainWidget->ui()->fileKurl->setText(idx.data(ThemeModel::PathRole).toString());
    m_mainWidget->ui()->wordEdit->setText(idx.data(ThemeModel::PathRole).toString());
    int index = m_mainWidget->ui()->comboBox_2->findText(idx.data(ThemeModel::LanguageRole).toString());
    if ( index != -1 )
    {
        m_mainWidget->ui()->comboBox_2->setCurrentIndex(index);
    }
    else
    {
        m_mainWidget->ui()->comboBox_2->addItem(idx.data(ThemeModel::LanguageRole).toString());
    }
    m_mainWidget->ui()->moreButton->show();
    qDebug() << "card Type" << type;
    if(!type)
    {
        m_mainWidget->widgetsHide();
        return;
    }
    m_mainWidget->ui()->langLabel->show();
    m_mainWidget->ui()->comboBox_2->show();
    QPixmap image;
    m_mainWidget->widgetsHide();
    switch(type)
    {
    case CARD_IMAGE:
        m_mainWidget->ui()->imageLabel->setText("Image file");
        m_mainWidget->ui()->imageLabel->show();
        m_mainWidget->ui()->itemLabel->show();
        m_mainWidget->ui()->fileKurl->show();
        image.load(m_pt->path()+"/"+m_mainWidget->ui()->fileKurl->text());
        m_mainWidget->ui()->itemLabel->setPixmap(image.scaledToWidth(100));
        break;
    case CARD_SOUND:
    case CARD_SOUNDLOGIC:
        m_mainWidget->ui()->imageLabel->setText("Sound file");
        m_mainWidget->ui()->imageLabel->show();
        m_mainWidget->ui()->fileKurl->show();
        break;
    case CARD_LOGIC:
        m_mainWidget->ui()->imageLabel->setText("Logic image file");
        m_mainWidget->ui()->itemLabel->show();
        m_mainWidget->ui()->imageLabel->show();
        m_mainWidget->ui()->fileKurl->show();
        image.load(m_pt->path()+"/"+m_mainWidget->ui()->fileKurl->text());
        m_mainWidget->ui()->itemLabel->setPixmap(image.scaledToWidth(100));
        break;
    case CARD_WORD:
        m_mainWidget->ui()->wordEdit->show();
        m_mainWidget->ui()->wordLabel->show();
        break;
    case CARD_FOUND:
        m_mainWidget->ui()->imageLabel->setText("Found sound file");
        m_mainWidget->ui()->imageLabel->show();
        m_mainWidget->ui()->fileKurl->show();
        break;

    }
}
void MainWindow::backSelected()
{
    QPixmap image;
    QString newFile = copyFile(m_mainWidget->ui()->backKurl);
    m_mainWidget->ui()->backKurl->setText(m_mainWidget->ui()->backKurl->url().fileName());
    image.load(newFile);
    m_mainWidget->ui()->pixLabel->setPixmap(image.scaledToWidth(100));
}
void MainWindow::fileSelected()
{
    QPixmap image;
    QString newFile = copyFile(m_mainWidget->ui()->fileKurl);
    m_mainWidget->ui()->fileKurl->setText(m_mainWidget->ui()->fileKurl->url().fileName());
    image.load(newFile);
    m_mainWidget->ui()->itemLabel->setPixmap(image.scaledToWidth(100));
    m_selectedItem->setData(m_mainWidget->ui()->fileKurl->text(),ThemeModel::PathRole);
    m_selectedItem->setText(m_mainWidget->ui()->fileKurl->text());

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
