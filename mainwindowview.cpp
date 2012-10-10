#include "mainwindowview.h"
#include "ui_mainwindowview.h"

MainWindowView::MainWindowView(QWidget *parent) : m_ui(new Ui::MainWindowView)
{
    m_ui->setupUi(this);
     m_ui->splitter->setStretchFactor(1, 3);
}

MainWindowView::~MainWindowView()
{
    delete m_ui;
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
                                