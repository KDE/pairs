#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSplitter.h>


MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),

    ui(new Ui::MainWindow)
{    QSplitter *splitter1 = new QSplitter(parent);
     QSplitter *splitter2 = new QSplitter(parent);
    splitter1->addWidget(treeview);
      splitter1->addWidget(widgetgroup);
      splitter2->addWidget(widgetgroup); splitter2->addWidget(helparea);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
