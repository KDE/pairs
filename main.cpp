#include "ptedit.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ptedit w;
    w.show();
    return a.exec();
}
