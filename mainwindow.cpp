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

void MainWindow::open(const QString& filename)
{
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
	QString filename = QFileDialog::getOpenFileName(this);
	
	if(!filename.isEmpty())
		open(filename);
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
