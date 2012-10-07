#include "mainwindow.h"
#include "pairstheme.h"
#include "thememodel.h"
#include "elementitem.h"
#include "featureitem.h"
#include "ui_mainwindow.h"
#include <QtGui/QFileDialog>
#include <QtCore/QDebug>
#include <kstandardaction.h>
#include <kaction.h>
#include <kdeversion.h>

MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
	pt = 0;
	m_model = 0;
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
    myact = new KAction(KIcon("go-up"), "Upload", ui->menu_file);
    connect(myact, SIGNAL(triggered(bool)), this, SLOT(doUpload()));
    ui->menu_file->addAction(myact);
    ui->toolBar->addAction(myact);
    myact = new KAction(KIcon("pairs"), "Try", ui->menu_file);
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
    m_checkMessage = "";
    if(ui->titleEdit->text().isEmpty())
    {
        m_checkMessage = "The Title is missing";
        return false;
    }
    if(ui->authorEdit->text().isEmpty())
    {
        m_checkMessage = "The Author is missing";
        return false;
    }
    if(ui->versionEdit->text().isEmpty())
    {
        m_checkMessage = "The Version is missing";
        return false;
    }
    if(ui->descriptionEdit->text().isEmpty())
    {
        m_checkMessage = "The Description is missing";
        return false;
    }
    if(ui->backKurl->text().isEmpty())
    {
        m_checkMessage = "The Back Image is missing";
        return false;
    }
    for (int i=0; i < m_model->rowCount(); i++)
    {
        ElementItem *myitem = static_cast<ElementItem*> (m_model->item(i,0));
        if(!myitem->check(i))
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
/*	m_model->appendRow(newItem);
	ui->treeView->update();
	ui->treeView->update();
*/
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
    m_file = QFileDialog::getSaveFileName(this, tr("Save Pairs theme"), QDir::currentPath(), tr("Pairs Themes (*.game)"));
    if(!m_file.isEmpty())
    {
        qDebug() << "Saving to " << m_file;
        doSave();
    }
}

void MainWindow::doNew()
{
    m_file = "";
    delete m_model;
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
	QFile f(m_file);
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
}


void MainWindow::open(const QString& filename)
{
	m_file = filename;
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
	m_file = QFileDialog::getOpenFileName(this, tr("Open Pairs theme"), QDir::currentPath(), tr("Pairs Themes (*.game)"));
	if(!m_file.isEmpty())
	{
	    QFileInfo pathInfo(m_file);
	    QDir::setCurrent(pathInfo.path());
		open(m_file);
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
	ui->backKurl->setText(ui->backKurl->url().fileName());
	image.load(pt->path()+"/"+ui->backKurl->text());
	ui->pixLabel->setPixmap(image.scaledToWidth(100));
}
void MainWindow::fileSelected()
{
	QPixmap image;
	ui->fileKurl->setText(ui->fileKurl->url().fileName());
	image.load(pt->path()+"/"+ui->fileKurl->text());
	ui->itemLabel->setPixmap(image.scaledToWidth(100));
	m_selectedItem->setData(ui->fileKurl->text(),ThemeModel::PathRole);
}
