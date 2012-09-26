#include "mainwindow.h"
#include "pairstheme.h"
#include "thememodel.h"
#include "ui_mainwindow.h"
#include <QtGui/QFileDialog>
#include <QtCore/QDebug>


MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
	pt = 0;
	ui->setupUi(this);
	connect(ui->action_open, SIGNAL(triggered()), this, SLOT(doOpen()));
	connect(ui->action_save, SIGNAL(triggered()), this, SLOT(doSave()));
	ui->imageLabel->hide();
	ui->fileKurl->hide();
	ui->itemLabel->show();
	ui->wordEdit->hide();
	ui->wordLabel->hide();
	ui->langLabel->hide();
	ui->comboBox_2->hide();
	
	connect(ui->fileKurl, SIGNAL(urlSelected(KUrl)), this, SLOT(fileSelected()));
	connect(ui->backKurl, SIGNAL(urlSelected(KUrl)), this, SLOT(backSelected()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::doSave()
{
	QFile f(m_file+".new");
	if (!f.open(QFile::WriteOnly | QFile::Text))
	{
			qWarning() << "Error: Cannot write file " << m_file;
			return;
	}

	QXmlStreamWriter stream(&f);
	stream.setAutoFormatting(true);
	stream.writeStartDocument();
	stream.writeAttribute("version", "1.0");
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
	stream.writeAttribute("type", ui->maintypeBox->currentText());
	stream.writeEndElement(); // main
	for (int i=0; i < m_model->rowCount(); i++)
	{
		QStandardItem *myitem = m_model->item(i,0);
		if(!myitem->data(ThemeModel::CardTypeRole).toInt())
		{
			if(i != 0)
				stream.writeEndElement();
			stream.writeStartElement("element");
			for (int i=0; i < myitem->rowCount(); i++)
			{
				QStandardItem *mysubitem = myitem->child(i,0);
				switch(mysubitem->data(ThemeModel::CardTypeRole).toInt())
				{
				case CARD_IMAGE:
				case CARD_LOGIC:
					stream.writeStartElement("image");
					stream.writeAttribute("src", mysubitem->data(ThemeModel::PathRole).toString());
					break;
				case CARD_SOUND:
				case CARD_SOUNDLOGIC:
					stream.writeStartElement("sound");
					stream.writeAttribute("src", mysubitem->data(ThemeModel::PathRole).toString());
					break;
				case CARD_FOUND:
					stream.writeStartElement("pfound");
					stream.writeAttribute("src", mysubitem->data(ThemeModel::PathRole).toString());
					break;
				case CARD_WORD:
					stream.writeStartElement("word");
					break;

				}
				stream.writeAttribute("lang", mysubitem->data(ThemeModel::LanguageRole).toString());
				if(mysubitem->data(ThemeModel::CardTypeRole).toInt() == CARD_WORD)
					stream.writeCharacters(mysubitem->data(ThemeModel::PathRole).toString());
				stream.writeEndElement();
			}
		}
	}
	stream.writeEndElement();//last element
	stream.writeEndElement(); // pairs
	stream.writeEndDocument();
}

void MainWindow::open(const QString& filename)
{
	m_file = filename;
	delete pt;
	pt = new PairsTheme(filename);
	m_model = new ThemeModel(*pt);
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
	QFileDialog fdialog(this);
	m_file = QFileDialog::getOpenFileName(this);
	
	if(!m_file.isEmpty())
		open(m_file);
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
	qDebug() << idx.data(ThemeModel::LanguageRole).toString() << index;
	if ( index != -1 )
	{
		ui->comboBox_2->setCurrentIndex(index);
	}
	else
	{
		ui->comboBox_2->addItem(idx.data(ThemeModel::LanguageRole).toString());
	}
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
	qDebug() << ".............." << ui->fileKurl->text() << m_selectedItem->text() << m_selectedItem->data(ThemeModel::PathRole);

}
