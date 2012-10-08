#include "mainwindow.h"
#include "pairstheme.h"
#include "thememodel.h"
#include "elementitem.h"
#include "featureitem.h"
#include "ui_mainwindow.h"
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <KAction>
#include <KStandardAction>
#include <kdeversion.h>
#include <KUrlRequester>
#include <KTar>

MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
	pt = 0;
	m_model = 0;
	m_tmpDir = 0;
	ui->setupUi(this);
    KAction *myact = KStandardAction::create(KStandardAction::New, this, SLOT(doNew()), ui->menu_file);
    ui->menu_file->addAction(myact);
    ui->toolBar->addAction(myact);
	myact = KStandardAction::create(KStandardAction::Open, this, SLOT(doOpen()), ui->menu_file);
	ui->menu_file->addAction(myact);
    ui->toolBar->addAction(myact);
    myact = KStandardAction::create(KStandardAction::Save, this, SLOT(doSave()), ui->menu_file);
    ui->menu_file->addAction(myact);
    ui->toolBar->addAction(myact);
    myact = KStandardAction::create(KStandardAction::SaveAs, this, SLOT(doSaveAs()), ui->menu_file);
    ui->menu_file->addAction(myact);
    ui->toolBar->addAction(myact);
    myact = new KAction(KIcon("go-up"), i18n("Upload"), ui->menu_file);
    connect(myact, SIGNAL(triggered(bool)), this, SLOT(doUpload()));
    ui->menu_file->addAction(myact);
    ui->toolBar->addAction(myact);
    myact = new KAction(KIcon("pairs"), i18n("Try"), ui->menu_file);
    connect(myact, SIGNAL(triggered(bool)), this, SLOT(doTry()));
    ui->menu_file->addAction(myact);
    ui->toolBar->addAction(myact);

    ui->imageLabel->hide();
	ui->fileKurl->hide();
	ui->itemLabel->show();
	ui->wordEdit->hide();
	ui->wordLabel->hide();
	ui->langLabel->hide();
	ui->comboBox_2->hide();
	ui->moreButton->hide();
	
	connect(ui->fileKurl, SIGNAL(urlSelected(KUrl)), this, SLOT(fileSelected()));
	connect(ui->backKurl, SIGNAL(urlSelected(KUrl)), this, SLOT(backSelected()));
	connect(ui->wordEdit, SIGNAL(textChanged(QString)), this, SLOT(wordChanged(QString)));
    connect(ui->delButton, SIGNAL(clicked()), this, SLOT(deleteElement()));
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addElement()));
    connect(ui->moreButton, SIGNAL(currentIndexChanged(int)), this, SLOT(addFeature(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::check()
{
    m_checkMessage.clear();
    if(ui->titleEdit->text().isEmpty())
    {
        m_checkMessage = i18n("The Title is missing");
        return false;
    }
    if(ui->authorEdit->text().isEmpty())
    {
        m_checkMessage = i18n("The Author is missing");
        return false;
    }
    if(ui->versionEdit->text().isEmpty())
    {
        m_checkMessage = i18n("The Version is missing");
        return false;
    }
    if(ui->descriptionEdit->text().isEmpty())
    {
        m_checkMessage = i18n("The Description is missing");
        return false;
    }
    if(ui->backKurl->text().isEmpty())
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
    ui->treeView->setModel(m_model);
    ui->titleEdit->setText("");
    ui->authorEdit->setText("");
    ui->versionEdit->setText("");
    ui->dateEdit->setDate(QDate::currentDate());
    ui->maintypeBox->setCurrentIndex(0);
    ui->descriptionEdit->setText("");
    ui->backKurl->setText("");
    ui->pixLabel->setPixmap(QPixmap());
    ui->fileKurl->setStartDir(KUrl(QDir::currentPath()));
    ui->backKurl->setStartDir(KUrl(QDir::currentPath()));
    ui->imageLabel->hide();
    ui->itemLabel->hide();
    ui->fileKurl->hide();
    ui->wordEdit->hide();
    ui->wordLabel->hide();
    ui->langLabel->hide();
    ui->comboBox_2->hide();
    ui->splitter->setStretchFactor(1, 3);
    connect(ui->treeView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), SLOT(selectionChanged(QItemSelection,QItemSelection)));

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
	stream.writeTextElement("title", ui->titleEdit->text());
	stream.writeTextElement("description", ui->descriptionEdit->text());
	stream.writeTextElement("author", ui->authorEdit->text());
	stream.writeTextElement("date", ui->dateEdit->text());
	stream.writeTextElement("version", ui->versionEdit->text());
	stream.writeStartElement("image");
	stream.writeAttribute("type", "back");
	stream.writeAttribute("src", ui->backKurl->text());
	stream.writeEndElement(); // image
	stream.writeStartElement("main");
	QString maintype = ui->maintypeBox->currentText();
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
//	m_file = filename;
	delete pt;
	pt = new PairsTheme(filename);
	m_model = new ThemeModel(*pt, this);
	ui->treeView->setModel(m_model);
	ui->titleEdit->setText(pt->title());
	ui->authorEdit->setText(pt->author());
	ui->versionEdit->setText(pt->version());
	ui->dateEdit->setDate(QDate::fromString(pt->date(),"d/M/yyyy"));
	ui->maintypeBox->setCurrentIndex(pt->mainType()-1);
	ui->descriptionEdit->setText(pt->description());
	ui->backKurl->setText(pt->backImage());
	QPixmap image(pt->path()+"/"+pt->backImage());
	ui->pixLabel->setPixmap(image.scaledToWidth(100));
	ui->fileKurl->setStartDir(KUrl(pt->path()));
	ui->backKurl->setStartDir(KUrl(pt->path()));
	ui->imageLabel->hide();
	ui->itemLabel->hide();
	ui->fileKurl->hide();
	ui->wordEdit->hide();
	ui->wordLabel->hide();
	ui->langLabel->hide();
	ui->comboBox_2->hide();
	ui->splitter->setStretchFactor(1, 3);
    connect(ui->treeView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), SLOT(selectionChanged(QItemSelection,QItemSelection)));
	
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
	ui->fileKurl->setText(idx.data(ThemeModel::PathRole).toString());
	ui->wordEdit->setText(idx.data(ThemeModel::PathRole).toString());
	int index = ui->comboBox_2->findText(idx.data(ThemeModel::LanguageRole).toString());
	if ( index != -1 )
	{
		ui->comboBox_2->setCurrentIndex(index);
	}
	else
	{
		ui->comboBox_2->addItem(idx.data(ThemeModel::LanguageRole).toString());
	}
    ui->moreButton->show();
    qDebug() << "card Type" << type;
	if(!type)
	{
		ui->imageLabel->hide();
		ui->itemLabel->hide();
		ui->fileKurl->hide();
		ui->wordEdit->hide();
		ui->wordLabel->hide();
		ui->langLabel->hide();
		ui->comboBox_2->hide();

		return;
	}
	ui->langLabel->show();
	ui->comboBox_2->show();
	QPixmap image;
	switch(type)
	{
	case CARD_IMAGE:
		ui->imageLabel->setText("Image file");
		ui->imageLabel->show();
		ui->itemLabel->show();
		ui->fileKurl->show();
		ui->wordEdit->hide();
		ui->wordLabel->hide();
		image.load(pt->path()+"/"+ui->fileKurl->text());
		ui->itemLabel->setPixmap(image.scaledToWidth(100));
		break;
	case CARD_SOUND:
	case CARD_SOUNDLOGIC:
		ui->imageLabel->setText("Sound file");
		ui->itemLabel->hide();
		ui->imageLabel->show();
		ui->fileKurl->show();
		ui->wordEdit->hide();
		ui->wordLabel->hide();
		break;
	case CARD_LOGIC:
		ui->imageLabel->setText("Logic image file");
		ui->itemLabel->show();
		ui->imageLabel->show();
		ui->fileKurl->show();
		ui->wordEdit->hide();
		ui->wordLabel->hide();
		image.load(pt->path()+"/"+ui->fileKurl->text());
		ui->itemLabel->setPixmap(image.scaledToWidth(100));
		break;
	case CARD_WORD:
		ui->imageLabel->hide();
		ui->itemLabel->hide();
		ui->fileKurl->hide();
		ui->wordEdit->show();
		ui->wordLabel->show();
		break;
	case CARD_FOUND:
		ui->imageLabel->setText("Found sound file");
		ui->itemLabel->hide();
		ui->imageLabel->show();
		ui->fileKurl->show();
		ui->wordEdit->hide();
		ui->wordLabel->hide();
		break;

	}
}
void MainWindow::backSelected()
{
	QPixmap image;
    QString newFile = copyFile(ui->backKurl);
    ui->backKurl->setText(ui->backKurl->url().fileName());
    image.load(newFile);
	ui->pixLabel->setPixmap(image.scaledToWidth(100));
}
void MainWindow::fileSelected()
{
	QPixmap image;
	QString newFile = copyFile(ui->fileKurl);
    ui->fileKurl->setText(ui->fileKurl->url().fileName());
	image.load(newFile);
	ui->itemLabel->setPixmap(image.scaledToWidth(100));
	m_selectedItem->setData(ui->fileKurl->text(),ThemeModel::PathRole);
    m_selectedItem->setText(ui->fileKurl->text());

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
