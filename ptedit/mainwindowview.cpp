#include "mainwindowview.h"
#include "mainwindow.h"
#include "ui_mainwindowview.h"
#include "pairstheme.h"
#include "thememodel.h"
#include "elementitem.h"
#include "thememodel.h"
#include "featureitem.h"
#include <QtGui/QTreeView>
#include <QXmlStreamWriter>
#include <QtCore/QDebug>

MainWindowView::MainWindowView(QWidget *parent) : m_ui(new Ui::MainWindowView)
{
	m_parent = static_cast<MainWindow*> (parent);
    m_ui->setupUi(this);
	m_ui->splitter->setStretchFactor(1, 3);
	connect(m_ui->fileKurl, SIGNAL(urlSelected(KUrl)), this, SLOT(fileSelected()));
	connect(m_ui->backKurl, SIGNAL(urlSelected(KUrl)), this, SLOT(backSelected()));
	connect(m_ui->wordEdit, SIGNAL(textChanged(QString)), this, SLOT(wordChanged(QString)));
	connect(m_ui->delButton, SIGNAL(clicked()), this, SLOT(deleteElement()));
	connect(m_ui->addButton, SIGNAL(clicked()), this, SLOT(addElement()));
	connect(m_ui->moreButton, SIGNAL(currentIndexChanged(int)), this, SLOT(addFeature(int)));

}

MainWindowView::~MainWindowView()
{
    delete m_ui;
}

void MainWindowView::setModel(ThemeModel *model)
{
	m_model = model;
	m_ui->treeView->setModel(model);
    connect(m_ui->treeView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), SLOT(selectionChanged(QItemSelection,QItemSelection)));
}

void MainWindowView::widgetsHide()
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

void MainWindowView::clearUi(const QString &path)
{
	m_path = path;
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
}

void MainWindowView::setUi(PairsTheme *theme)
{
	m_pt = theme;
	m_path = m_pt->path();
	m_ui->titleEdit->setText(theme->title());
	m_ui->authorEdit->setText(theme->author());
	m_ui->versionEdit->setText(theme->version());
	m_ui->dateEdit->setDate(QDate::fromString(theme->date(),"d/M/yyyy"));
	m_ui->maintypeBox->setCurrentIndex(theme->mainType()-1);
	m_ui->descriptionEdit->setText(theme->description());
	m_ui->backKurl->setText(theme->backImage());
	QPixmap image(m_path +"/"+theme->backImage());
	m_ui->pixLabel->setPixmap(image.scaledToWidth(100));
	m_ui->fileKurl->setStartDir(KUrl(theme->path()));
	m_ui->backKurl->setStartDir(KUrl(theme->path()));
}

void MainWindowView::writeXmlCommon(QXmlStreamWriter *stream)
{
	stream->writeTextElement("title", m_ui->titleEdit->text());
	stream->writeTextElement("description", m_ui->descriptionEdit->text());
	stream->writeTextElement("author", m_ui->authorEdit->text());
	stream->writeTextElement("date", m_ui->dateEdit->text());
	stream->writeTextElement("version", m_ui->versionEdit->text());
	stream->writeStartElement("image");
	stream->writeAttribute("type", "back");
	stream->writeAttribute("src", m_ui->backKurl->text());
	stream->writeEndElement(); // image
	stream->writeStartElement("main");
	QString maintype = m_ui->maintypeBox->currentText();
	if(maintype == "relation")
		maintype = "image";
	stream->writeAttribute("type", maintype);
	stream->writeEndElement(); // main
}


bool MainWindowView::check()
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

void MainWindowView::addFeature(int index)
{
    QStandardItem *paren = m_selectedItem;
    m_ui->moreButton->setCurrentIndex(-1);
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

void MainWindowView::addElement()
{
    if(m_selectedItem->data(ThemeModel::CardTypeRole).toInt())
        return;
    const ThemeElement el;
    ElementItem *newItem = new ElementItem (el);
    QString name = i18n("Element %1", m_model->rowCount()+1);
    newItem->setText(name);
    m_model->insertItem(newItem);
}

void MainWindowView::deleteElement()
{
    m_model->removeItem(m_selectedItem);
}
void MainWindowView::selectionChanged(const QItemSelection& selected, const QItemSelection&  )
{
    if(!selected.isEmpty())
        elementSelected(selected.indexes().first());
}

void MainWindowView::elementSelected(const QModelIndex & idx)
{
    m_selectedItem = m_model->itemFromIndex(idx);
    int type = idx.data(ThemeModel::CardTypeRole).toInt();
    if(!type)
    {
        widgetsHide();
        m_ui->moreButton->show();
        return;
    }
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
    qDebug() << "card Type" << type;
    QPixmap image;
    widgetsHide();
    m_ui->moreButton->show();
    m_ui->langLabel->show();
    m_ui->comboBox_2->show();
    switch(type)
    {
    case CARD_IMAGE:
        m_ui->imageLabel->setText("Image file");
        m_ui->imageLabel->show();
        m_ui->itemLabel->show();
        m_ui->fileKurl->show();
        image.load(m_path+"/"+m_ui->fileKurl->text());
        m_ui->itemLabel->setPixmap(image.scaledToWidth(100));
        break;
    case CARD_SOUND:
    case CARD_SOUNDLOGIC:
        m_ui->imageLabel->setText("Sound file");
        m_ui->imageLabel->show();
        m_ui->fileKurl->show();
        break;
    case CARD_LOGIC:
        m_ui->imageLabel->setText("Logic image file");
        m_ui->itemLabel->show();
        m_ui->imageLabel->show();
        m_ui->fileKurl->show();
        image.load(m_path+"/"+m_ui->fileKurl->text());
        m_ui->itemLabel->setPixmap(image.scaledToWidth(100));
        break;
    case CARD_WORD:
        m_ui->wordEdit->show();
        m_ui->wordLabel->show();
        break;
    case CARD_FOUND:
        m_ui->imageLabel->setText("Found sound file");
        m_ui->imageLabel->show();
        m_ui->fileKurl->show();
        break;

    }
}
void MainWindowView::backSelected()
{
    QPixmap image;
    QString newFile = m_parent->copyFile(m_ui->backKurl);
    m_ui->backKurl->setText(m_ui->backKurl->url().fileName());
    image.load(newFile);
    m_ui->pixLabel->setPixmap(image.scaledToWidth(100));
}
void MainWindowView::fileSelected()
{
    QPixmap image;
    QString newFile = m_parent->copyFile(m_ui->fileKurl);
    m_ui->fileKurl->setText(m_ui->fileKurl->url().fileName());
    image.load(newFile);
    m_ui->itemLabel->setPixmap(image.scaledToWidth(100));
    m_selectedItem->setData(m_ui->fileKurl->text(),ThemeModel::PathRole);
    m_selectedItem->setText(m_ui->fileKurl->text());

}

void MainWindowView::wordChanged(const QString &word)
{
    m_selectedItem->setData(word, ThemeModel::PathRole);
    m_selectedItem->setText(word);
}

