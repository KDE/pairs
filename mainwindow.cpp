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
	ui->setupUi(this);
	connect(ui->action_open, SIGNAL(triggered()), this, SLOT(doOpen()));
	ui->imageLabel->hide();
	ui->fileKurl->hide();
	ui->wordEdit->hide();
	ui->wordLabel->hide();
	ui->langLabel->hide();
	ui->comboBox_2->hide();
	connect(ui->treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(elementSelected(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::doOpen()
{
	QFileDialog fdialog(this);
	QString filename = QFileDialog::getOpenFileName(this);
	PairsTheme pt(filename);
	ThemeModel *model = new ThemeModel(pt);
	ui->treeView->setModel(model);
	ui->titleEdit->setText(pt.title());
	ui->authorEdit->setText(pt.author());
	ui->versionEdit->setText(pt.version());
	ui->dateEdit->setDate(QDate::fromString(pt.date(),"d/M/yyyy"));
	ui->maintypeBox->setCurrentIndex(pt.mainType()-1);
	ui->descriptionEdit->setText(pt.description());
	ui->backKurl->setText(pt.backImage());
	QByteArray file_buf = (pt.themeData(pt.backImage()));
	QPixmap image;
	image.loadFromData(file_buf);
	ui->pixLabel->setPixmap(image.scaledToWidth(100));

}

void MainWindow::elementSelected(const QModelIndex & item)
{
	int type = item.data(ThemeModel::CardTypeRole).toInt();
	ui->fileKurl->setText(item.data(ThemeModel::PathRole).toString());
	ui->wordEdit->setText(item.data(ThemeModel::PathRole).toString());
	int index = ui->comboBox_2->findData(item.data(ThemeModel::LanguageRole).toString());
	if ( index != -1 )
	{
		ui->comboBox_2->setCurrentIndex(index);
	}
	else
	{
		ui->comboBox_2->addItem(item.data(ThemeModel::LanguageRole).toString());
	}
	if(!type)
		return;
	ui->langLabel->show();
	ui->comboBox_2->show();
	switch(type)
	{
	case CARD_IMAGE:
	case CARD_IMAGE2:
		ui->imageLabel->setText("Image file");
		ui->imageLabel->show();
		ui->fileKurl->show();
		ui->wordEdit->hide();
		ui->wordLabel->hide();
		break;
	case CARD_SOUND:
	case CARD_SOUNDLOGIC:
		ui->imageLabel->setText("Sound file");
		ui->imageLabel->show();
		ui->fileKurl->show();
		ui->wordEdit->hide();
		ui->wordLabel->hide();
		break;
	case CARD_LOGIC:
		ui->imageLabel->setText("Logic image file");
		ui->imageLabel->show();
		ui->fileKurl->show();
		ui->wordEdit->hide();
		ui->wordLabel->hide();
		break;
	case CARD_WORD:
		ui->imageLabel->hide();
		ui->fileKurl->hide();
		ui->wordEdit->show();
		ui->wordLabel->show();
		break;
	case CARD_FOUND:
		ui->imageLabel->setText("Found sound file");
		ui->imageLabel->show();
		ui->fileKurl->show();
		ui->wordEdit->hide();
		ui->wordLabel->hide();
		break;

	}




}

