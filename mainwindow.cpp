#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSplitter>


MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),

    ui(new Ui::MainWindow)
{    QSplitter *splitter1 = new QSplitter(parent);
     QSplitter *splitter2 = new QSplitter(parent);
    splitter1->addWidget( ui->treeWidget);
      splitter1->addWidget(ui->groupBox);

      splitter2->addWidget(ui->groupBox); splitter2->addWidget(ui->scrollArea);




    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
