#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    if(argc>1)
        w.open(a.arguments()[1]);
    w.show();
    
    return a.exec();
}
